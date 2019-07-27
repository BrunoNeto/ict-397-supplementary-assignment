#pragma once
#pragma once
#include "npc.h"
#include "IGameAsset.h"
#include <set>
#include <vector>
#include <glm/gtx/norm.hpp>
using namespace std;
using namespace glm;
//Our data structure for making collision detection faster

const int MAX_OCTREE_DEPTH = 6;
const int MIN_ASSET_PER_OCTREE = 3;
const int MAX_ASSET_PER_OCTREE = 6;
//*@brief struct needed for collision detection
struct AssetPair {
	IGameAsset* iGameAsset1;
	IGameAsset* iGameAsset2;
};
//*@brief struct needed for collision detection
enum Wall { WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };
//Stores a IGameAsset and a wall
//*@brief struct needed for collision detection
struct AssetWallPair {
	IGameAsset* asset;
	Wall wall;
};




//*@brief data structure for collision detection
class Octree {
private:
	vec3 corner1; //(minX, minY, minZ)
	vec3 corner2; //(maxX, maxY, maxZ)
	vec3 center;//((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2)
	float BOX_SIZE;
	/* The children of this, if this has any.  children[0][*][*] are the
		 * children with x coordinates ranging from minX to centerX.
		 * children[1][*][*] are the children with x coordinates ranging from
		 * centerX to maxX.  Similarly for the other two dimensions of the
		 * children array.
		 */
	Octree *children[2][2][2];
	//Whether this has children
	bool hasChildren;
	//The assets in this, if this doesn't have any children
	set<IGameAsset*> assets;
	//The depth of this in the tree
	int depth;
	//The number of assets in this, including those stored in its children
	int numAssets;
	//
	/**
	*	@brief  Adds a IGameAsset to or removes a from one to the children of this
	*   @see
	*	@param IGameAsset
	*	@param pos
	*	@param addAsset
	*	@return void
	*	@pre
	*	@post
	*/
	void fileAsset(IGameAsset* IGameAsset, vec3 pos, bool addAsset);


	//
	/**
	*	@brief  Creates children of this, and moves the IGameAsset in this to the children
	*   @see
	*	@return void
	*	@pre
	*	@post
	*/
	void haveChildren();

	
	/**
	*	@brief Destroys the children of this, and moves all assets in its descendants to the "assets" set
	*   @see
	*	@return void
	*	@pre
	*	@post
	*/
	void destroyChildren();

	//
	/**
	*	@brief Removes the specified IGameAsset at the indicated position
	*   @see
	*	@param IGameAsset
	*	@param pos
	*	@return void
	*	@pre
	*	@post
	*/
	void remove(IGameAsset* IGameAsset, vec3 pos);
	
public:

	/**
	*	@brief Constructs a new Octree.  c1 is (minX, minY, minZ), c2 is (maxX, maxY, maxZ), and d is the depth, which starts at 1., size is the size in x or z in world (assumes cube shape)
	*   @see
	*	@param c1 min point of the box
	*	@param c2 max point of the box
	*	@param d the max depth to set on the octree
	*	@param Size the length of a side of the cube that makes up world
	*	@return 
	*	@pre
	*	@post
	*/
	Octree(vec3 c1, vec3 c2, int d, float size);

	//Destructor
	//
	/**
	*	@brief deconstructs
	*   @see
	*	@return
	*	@pre
	*	@post
	*/
	~Octree();

	//
	/**
	*	@brief Adds a IGameAsset to this
	*   @see
	*	@param asset asset to add to treee
	*	@return void
	*	@pre
	*	@post
	*/
	void add(IGameAsset* asset);

	
	/**
	*	@brief Removes a IGameAsset  from this treee
	*   @see
	*	@param asset the asset to remove
	*	@return void
	*	@pre
	*	@post
	*/
	void remove(IGameAsset* asset);

	
	/**
	*	@brief Changes the position of a IGameAsset in this from oldPos to IGameAsset->position
	*   @see
	*	@param asset the asset in question
	*	@param old pos the old pos of the asset
	*	@return void
	*	@pre
	*	@post
	*/
	void AssetMoved(IGameAsset* asset, vec3 oldPos);


	
	/**
	*	@brief Adds potential IGameAsset-IGameAsset collisions vector to the specified set
	*   @see
	*	@param collisions a vector of igame asset pair structure
	*	@return void
	*	@pre
	*	@post
	*/
	void PotentialIGameAssetIGameAssetCollisions(vector<AssetPair> &collisions);
	//
	/**
	*	@brief Adds all assets in this or one of its descendants to the specified set
	*   @see
	*	@param as a set of game assets
	*	@return void
	*	@pre
	*	@post
	*/
	void collectAssets(set<IGameAsset*> &as);

	//
	/**
	*	@brief Returns whether two assets are colliding
	*   @see
	*	@param n1 a game asset pointer
	*	@param n2 another game asset to compare against
	*	@return bool
	*	@pre
	*	@post
	*/
	bool testIGameAssetIGameAssetCollision(IGameAsset* n1, IGameAsset* n2);

	//
	/**
	*	@brief Handles all asset-asset collisions
	*   @see
	*	@param assets a vector of igame assets pointer
	*	@param octree am octree pointer
	*	@return void
	*	@pre
	*	@post
	*/
	void handleIGameAssetIGameAssetCollisions(vector<IGameAsset*> &assets, Octree* octree);

	//
	/**
	*	@brief Returns whether a IGameAsset and a wall are colliding
	*   @see
	*	@param iGameAsset1 a game asset
	*	@param wall a border of the world
	*	@return bool
	*	@pre
	*	@post
	*/
	bool testIGameAssetWallCollision(IGameAsset* iGameAsset1, Wall wall);

	//
	//
	/**
	*	@brief Puts potential IGameAsset-IGameAsset collisions in potentialCollisions.  It must return all actual collisions, but it need not return only actual collisions.
	*   @see
	*	@param potential collisions a vector of asset pairs structures
	*	@param assets a vector of asset pointer, reference
	*	@param octree an octree pointer
	*	@return void
	*	@pre
	*	@post
	*/
	void PotentialIGameAssetIGameAssetCollisions(vector<AssetPair> &potentialCollisions, vector<IGameAsset*> &assets, Octree* octree);
	
	//
	/**
	*	@brief Returns the direction from the origin to the wall
	*   @see
	*	@param wall a border of the game world
	*	@return
	*	@pre
	*	@post
	*/
	vec3 wallDirection(Wall wall);
	

};




































































