#include "Octree.h"
void Octree::fileAsset(IGameAsset* IGameAsset, vec3 pos, bool addAsset) {
	//Figure out in which child(ren) the IGameAsset belongs
	for (int x = 0; x < 2; x++) {
		if (x == 0) {
			if (pos[0] - IGameAsset->r > center[0]) {
				continue;
			}
		}
		else if (pos[0] + IGameAsset->r < center[0]) {
			continue;
		}

		for (int y = 0; y < 2; y++) {
			if (y == 0) {
				if (pos[1] - IGameAsset->r > center[1]) {
					continue;
				}
			}
			else if (pos[1] + IGameAsset->r < center[1]) {
				continue;
			}

			for (int z = 0; z < 2; z++) {
				if (z == 0) {
					if (pos[2] - IGameAsset->r > center[2]) {
						continue;
					}
				}
				else if (pos[2] + IGameAsset->r < center[2]) {
					continue;
				}

				//Add or remove the IGameAsset
				if (addAsset) {
					children[x][y][z]->add(IGameAsset);
				}
				else {
					children[x][y][z]->remove(IGameAsset, pos);
				}
			}
		}
	}
}


//Creates children of this, and moves the IGameAsset in this to the children
void Octree::haveChildren() {
	for (int x = 0; x < 2; x++) {
		float minX;
		float maxX;
		if (x == 0) {
			minX = corner1[0];
			maxX = center[0];
		}
		else {
			minX = center[0];
			maxX = corner2[0];
		}

		for (int y = 0; y < 2; y++) {
			float minY;
			float maxY;
			if (y == 0) {
				minY = corner1[1];
				maxY = center[1];
			}
			else {
				minY = center[1];
				maxY = corner2[1];
			}

			for (int z = 0; z < 2; z++) {
				float minZ;
				float maxZ;
				if (z == 0) {
					minZ = corner1[2];
					maxZ = center[2];
				}
				else {
					minZ = center[2];
					maxZ = corner2[2];
				}

				children[x][y][z] = new Octree(vec3(minX, minY, minZ), vec3(maxX, maxY, maxZ), depth + 1, BOX_SIZE);
			}
		}
	}

	//Remove all assets from "assets" and add them to the new children
	for (set<IGameAsset*>::iterator it = assets.begin(); it != assets.end(); it++)
	{
		IGameAsset* IGameAsset = *it;
		fileAsset(IGameAsset, IGameAsset->GetPosition(), true);
	}
	assets.clear();

	hasChildren = true;
}

//Destroys the children of this, and moves all assets in its descendants
	//to the "assets" set
void Octree::destroyChildren() {
	//Move all assets in descendants of this to the "assets" set
	collectAssets(assets);

	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 2; z++) {
				delete children[x][y][z];
			}
		}
	}

	hasChildren = false;
}

//Removes the specified IGameAsset at the indicated position
void Octree::remove(IGameAsset* IGameAsset, vec3 pos) {
	numAssets--;

	if (hasChildren && numAssets < MIN_ASSET_PER_OCTREE) {
		destroyChildren();
	}

	if (hasChildren) {
		fileAsset(IGameAsset, pos, false);
	}
	else {
		assets.erase(IGameAsset);
	}
}
/* Helper fuction for potentialIGameAssetWallCollisions(vector).  Adds
	 * potential IGameAsset-wall collisions to cs, where w is the type of wall,
	 * coord is the relevant coordinate of the wall ('x', 'y', or 'z'), and
	 * dir is 0 if the wall is in the negative direction and 1 if it is in
	 * the positive direction.  Assumes that this is in the extreme
	 * direction of the coordinate, e.g. if w is WALL_TOP, the function
	 * assumes that this is in the far upward direction.
	 */
	 /*void potentialIGameAssetWallCollisions(vector<AssetWallPair> &cs,Wall w, char coord, int dir) {
		 if (hasChildren) {
			 //Recursively call potentialBallWallCollisions on the correct
			 //half of the children (e.g. if w is WALL_TOP, call it on
			 //children above centerY)
			 for (int dir2 = 0; dir2 < 2; dir2++) {
				 for (int dir3 = 0; dir3 < 2; dir3++) {
					 Octree *child;
					 switch (coord) {
					 case 'x':
						 child = children[dir][dir2][dir3];
						 break;
					 case 'y':
						 child = children[dir2][dir][dir3];
						 break;
					 case 'z':
						 child = children[dir2][dir3][dir];
						 break;
					 }

					 child->potentialIGameAssetWallCollisions(cs, w, coord, dir);
				 }
			 }
		 }
		 else {
			 //Add (IGameAsset, w) for all assets in this
			 for (set<IGameAsset*>::iterator it = assets.begin(); it != assets.end();it++)
			 {
				 IGameAsset* IGameAsset  = *it;
				 AssetWallPair nwp;
				 nwp.asset = IGameAsset;
				 nwp.wall = w;
				 cs.push_back(nwp);
			 }
		 }
	 }*/

	//Constructs a new Octree.  c1 is (minX, minY, minZ), c2 is (maxX, maxY,
		//maxZ), and d is the depth, which starts at 1., size is the size in x or z in world (assumes cube shape) 
Octree::Octree(vec3 c1, vec3 c2, int d, float size)
	{
		BOX_SIZE = size;
		corner1 = c1;
		corner2 = c2;
		center.x = (c1.x + c2.x) / 2;
		center.y = (c1.y + c2.y) / 2;
		center.z = (c1.z + c2.z) / 2;
		depth = d;
		numAssets = 0;
		hasChildren = false;
	}

	//Destructor
Octree::~Octree()
	{
		if (hasChildren) {
			destroyChildren();
		}
	}
	//Adds a IGameAsset to this
	void Octree::add(IGameAsset* asset)
	{
		numAssets++;
		if (!hasChildren && depth < MAX_OCTREE_DEPTH && numAssets > MAX_ASSET_PER_OCTREE)
		{
			haveChildren();
		}
		if (hasChildren) {
			fileAsset(asset, asset->GetPosition(), true);
		}
		else {
			assets.insert(asset);
		}
	}

	//Removes a IGameAsset  from this
	void Octree::remove(IGameAsset* asset) {
		remove(asset, asset->GetPosition());
	}

	//Changes the position of a IGameAsset in this from oldPos to IGameAsset->position
	void Octree::AssetMoved(IGameAsset* asset, vec3 oldPos) {
		remove(asset, oldPos);
		add(asset);
	}


	//Adds potential IGameAsset-IGameAsset collisions to the specified set
	void Octree::PotentialIGameAssetIGameAssetCollisions(vector<AssetPair> &collisions) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 2; y++) {
					for (int z = 0; z < 2; z++) {
						children[x][y][z]->
							PotentialIGameAssetIGameAssetCollisions(collisions);
					}
				}
			}
		}
		else {
			//Add all pairs (asset1, asset2) from assets
			for (set<IGameAsset*>::iterator it = assets.begin(); it != assets.end(); it++)
			{
				IGameAsset* iGameAsset1 = *it;
				for (set<IGameAsset*>::iterator it2 = assets.begin(); it2 != assets.end(); it2++)
				{
					IGameAsset *iGameAsset2 = *it2;
					//This test makes sure that we only add each pair once
					if (iGameAsset1 < iGameAsset2) {
						AssetPair ap;
						ap.iGameAsset1 = iGameAsset1;
						ap.iGameAsset2 = iGameAsset2;
						collisions.push_back(ap);
					}
				}
			}
		}
	}
	//Adds all assets in this or one of its descendants to the specified set
	void Octree::collectAssets(set<IGameAsset*> &as) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 2; y++) {
					for (int z = 0; z < 2; z++) {
						children[x][y][z]->collectAssets(as);
					}
				}
			}
		}
		else {
			for (set<IGameAsset*>::iterator it = assets.begin(); it != assets.end();
				it++) {
				IGameAsset* asset = *it;
				as.insert(asset);
			}
		}
	}
	//Returns whether two assets are colliding
	bool Octree::testIGameAssetIGameAssetCollision(IGameAsset* n1, IGameAsset* n2) {
		//Check whether the assets are close enough
		float r = n1->r + n2->r;
		if (length2(n1->GetPosition() - n2->GetPosition()) < r ) {
			//Check whether the assets are moving toward each other not needed causes bad stuff to happen like multiple models inheriting same location
			//vec3 netVelocity = n1->GetVelocity() - n2->GetVelocity();
			//vec3 displacement = n1->GetPosition() - n2->GetPosition();
			//return dot(netVelocity, displacement) < 0;
			
			return true;
		}
		else
			return false;
	}

	//Handles all asset-asset collisions
	void Octree::handleIGameAssetIGameAssetCollisions(vector<IGameAsset*> &assets, Octree* octree) {
		vector<AssetPair> aps;
		PotentialIGameAssetIGameAssetCollisions(aps, assets, octree);
		for (unsigned int i = 0; i < aps.size(); i++) {
			AssetPair ap = aps[i];
			
			IGameAsset* n1 = ap.iGameAsset1;
			IGameAsset* n2 = ap.iGameAsset2;
			if (testIGameAssetIGameAssetCollision(n1, n2)) {
				//Make the assets reflect off of each other
			
				//vec3 displacement = n2->GetPosition() - n1->GetPosition();
				//displacement.x = displacement.x * n1->r;//* n2->r;
				//displacement.y = displacement.y * n1->r;//* n2->r;
				//displacement.z = displacement.z * n1->r; //*n2->r;
				
				
				n1->velocity = reflect(n1->velocity,n2->GetPosition()); //(displacement * dot(n2->velocity, displacement));
				n1->TriggerWander();//only affects npcs
				
				
				n2->velocity = reflect(n2->velocity, n1->GetPosition()); //(displacement * dot(n1->velocity, displacement));
				//trigger new wander after reflect
				n2->TriggerWander();
				
			}
		}
	}
	//Returns whether a IGameAsset and a wall are colliding
	bool Octree::testIGameAssetWallCollision(IGameAsset* iGameAsset1, Wall wall)
	{
		vec3 dir = wallDirection(wall);
		//Check whether the IGameAsset is far enough in the "dir" direction, and whether
		//it is moving toward the wall 
		return dot(iGameAsset1->GetPosition(), dir) + iGameAsset1->r > BOX_SIZE / 2 &&
			dot(iGameAsset1->GetVelocity(), dir) > 0;
	}

	//Handles all asset-wall collisions
	//void handleNpcWallCollisions(vector<IGameAsset*> &assets, Octree* octree) {
	//	vector<AssetWallPair> nwps;
	//	potentialIGameAssetWallCollisions(nwps, assets, octree);
	//	for (unsigned int i = 0; i < nwps.size(); i++) {
	//		AssetWallPair nwp = nwps[i];
	//
	//		IGameAsset* n = nwp.asset;
	//		Wall w = nwp.wall;
	//		if (testIGameAssetWallCollision(n, w)) {
	//			//Make the IGameAsset reflect off of the wall
	//			vec3 dir = normalize((wallDirection(w)));
	//			dir.x = dir.x * 2;
	//			dir.y = dir.y * 2;
	//			dir.z = dir.z * 2;
	//			n->velocity -=  dir * dot(n->velocity,dir);
	//		}
	//	}
	//}


	//Adds potential IGameAsset-wall collisions to the specified set
	//void potentialIGameAssetWallCollisions(vector<AssetWallPair> &collisions) {
	//	potentialIGameAssetWallCollisions(collisions, WALL_LEFT, 'x', 0);
	//	potentialIGameAssetWallCollisions(collisions, WALL_RIGHT, 'x', 1);
	//	potentialIGameAssetWallCollisions(collisions, WALL_BOTTOM, 'y', 0);
	//	potentialIGameAssetWallCollisions(collisions, WALL_TOP, 'y', 1);
	//	potentialIGameAssetWallCollisions(collisions, WALL_FAR, 'z', 0);
	//	potentialIGameAssetWallCollisions(collisions, WALL_NEAR, 'z', 1);
	//}


//Puts potential IGameAsset-IGameAsset collisions in potentialCollisions.  It must return
//all actual collisions, but it need not return only actual collisions.
	void Octree::PotentialIGameAssetIGameAssetCollisions(vector<AssetPair> &potentialCollisions, vector<IGameAsset*> &assets, Octree* octree)
	{
		//Fast method
		octree->PotentialIGameAssetIGameAssetCollisions(potentialCollisions);

		/*
		//Slow method
		for(unsigned int i = 0; i < assets.size(); i++) {
			for(unsigned int j = i + 1; j < assets.size(); j++) {
				BallPair bp;
				bp.ball1 = assets[i];
				bp.ball2 = assets[j];
				potentialCollisions.push_back(bp);
			}
		}
		*/
	}


	//Puts potential IGameAsset-wall collisions in potentialCollisions.  It must return
	//all actual collisions, but it need not return only actual collisions.
	//void potentialIGameAssetWallCollisions(vector<AssetWallPair> &potentialCollisions,
		//vector<IGameAsset*> &assets, Octree* octree) 
	//{
		//Fast method
		//octree->potentialIGameAssetWallCollisions(potentialCollisions);

		/*
		//Slow method
		Wall walls[] =
			{WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM};
		for(unsigned int i = 0; i < assets.size(); i++) {
			for(int j = 0; j < 6; j++) {
				BallWallPair bwp;
				bwp.IGameAsset = assets[i];
				bwp.wall = walls[j];
				potentialCollisions.push_back(bwp);
			}
		}
		*/
		//}

			//Returns the direction from the origin to the wall
	vec3 Octree::wallDirection(Wall wall) {
		switch (wall) {
		case WALL_LEFT:
			return vec3(-1, 0, 0);
		case WALL_RIGHT:
			return vec3(1, 0, 0);
		case WALL_FAR:
			return vec3(0, 0, -1);
		case WALL_NEAR:
			return vec3(0, 0, 1);
		case WALL_TOP:
			return vec3(0, 1, 0);
		case WALL_BOTTOM:
			return vec3(0, -1, 0);
		default:
			return vec3(0, 0, 0);
		}
	}