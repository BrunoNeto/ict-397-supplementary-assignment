#include "Terrain.h"
//	@brief World class for our world object
//	@todo once i have figured out everything world need it must be seperated int 2 classes one with data and the other as a controller
//	@author Bruno Neto
//	version 1.0
class World
{
public:
	/**
	*	@brief World default contructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	World();

	/**
	*	@brief world deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~World();

	/**
	*	@brief render function for world, calls the render function of terrain in world
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void Render();

	/**
	*	@brief method for getting the size of the heightmap for ref terrain is [size*size] big
	*   @see
	*	@param
	*	@return the size of the world in integer
	*	@pre
	*	@post
	*/
	int getWorldSize();

	/**
	*	@brief method for getting the height at particular x,z location
	*   @see
	*	@param x the x value we need hight for
	*	@param z the z value we need hight for
	*	@return returns a float value of the height(unscaled) at location x,z
	*	@pre
	*	@post
	*/
	float getWorldXZHeight(float x, float z);

	/**
	*	@brief method for checking if the x,z point is withing the terrain loaded in the world
	*   @see
	*	@param x the x value we need to check if is in terrain
	*	@param z the z value we need to check if is in terrain
	*	@return
	*	@pre
	*	@post
	*/
	float inWorld(float& x, float& z);

	/**
	*	@brief method for getting the scaled height at particular x,z location
	*   @see
	*	@param x the x value we need hight for
	*	@param z the z value we need hight for
	*	@return returns a float value of the scaled height at location x,z
	*	@pre
	*	@post
	*/
	float getScaledHeight(float x, float z);

	/**
	*	@brief method for loading the objects and variables that make up a world
	*   @see
	*	@param
	*	@return returns true if successfull
	*	@pre
	*	@post
	*/
	bool loadWorld();

	/**
	*	@brief method for un loading the objects and variables that make up a world
	*   @see
	*	@param
	*	@return returns true if successfull
	*	@pre
	*	@post
	*/
	void unLoadWorld();

	/**
	*	@brief method for loading the pre set terrain texture into the terrain of world
	*   @see
	*	@param
	*	@return returns true if successfull
	*	@pre
	*	@post
	*/
	bool loadWorldTexture();

private:
	Terrain t;
	
};

