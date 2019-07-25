#pragma once
#include "npc.h"
#include <set>
#include <vector>
#include <glm/gtx/norm.hpp>
using namespace std;
using namespace glm;
//Our data structure for making collision detection faster

const int MAX_OCTREE_DEPTH = 6;
const int MIN_NPCS_PER_OCTREE = 3;
const int MAX_NPCS_PER_OCTREE = 5;

struct NpcPair {
	npc* npc1;
	npc* npc2;
};
enum Wall { WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };
//Stores a npc and a wall
struct NpcWallPair {
	npc* Npc;
	Wall wall;
};





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
	//The npcs in this, if this doesn't have any children
	set<npc*> npcs;
	//The depth of this in the tree
	int depth;
	//The number of npcs in this, including those stored in its children
	int numNpcs;
	//Adds a npc to or removes a from one to the children of this
	void fileNpc(npc* npc, vec3 pos, bool addNpc) {
		//Figure out in which child(ren) the npc belongs
		for (int x = 0; x < 2; x++) {
			if (x == 0) {
				if (pos[0] - npc->r > center[0]) {
					continue;
				}
			}
			else if (pos[0] + npc->r < center[0]) {
				continue;
			}

			for (int y = 0; y < 2; y++) {
				if (y == 0) {
					if (pos[1] - npc->r > center[1]) {
						continue;
					}
				}
				else if (pos[1] + npc->r < center[1]) {
					continue;
				}

				for (int z = 0; z < 2; z++) {
					if (z == 0) {
						if (pos[2] - npc->r > center[2]) {
							continue;
						}
					}
					else if (pos[2] + npc->r < center[2]) {
						continue;
					}

					//Add or remove the npc
					if (addNpc) {
						children[x][y][z]->add(npc);
					}
					else {
						children[x][y][z]->remove(npc, pos);
					}
				}
			}
		}
	}

	//Creates children of this, and moves the npc in this to the children
	void haveChildren() {
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

					children[x][y][z] = new Octree(vec3(minX, minY, minZ),vec3(maxX, maxY, maxZ),depth + 1,BOX_SIZE);
				}
			}
		}

		//Remove all npcs from "npcs" and add them to the new children
		for (set<npc*>::iterator it = npcs.begin(); it != npcs.end();it++) 
		{
			npc* npc = *it;
			fileNpc(npc, npc->GetPosition(), true);
		}
		npcs.clear();

		hasChildren = true;
	}

	//Destroys the children of this, and moves all npcs in its descendants
		//to the "npcs" set
	void destroyChildren() {
		//Move all npcs in descendants of this to the "npcs" set
		collectNpcs(npcs);

		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				for (int z = 0; z < 2; z++) {
					delete children[x][y][z];
				}
			}
		}

		hasChildren = false;
	}

	//Removes the specified npc at the indicated position
	void remove(npc* npc, vec3 pos) {
		numNpcs--;

		if (hasChildren && numNpcs < MIN_NPCS_PER_OCTREE) {
			destroyChildren();
		}

		if (hasChildren) {
			fileNpc(npc, pos, false);
		}
		else {
			npcs.erase(npc);
		}
	}
	/* Helper fuction for potentialNpcWallCollisions(vector).  Adds
		 * potential npc-wall collisions to cs, where w is the type of wall,
		 * coord is the relevant coordinate of the wall ('x', 'y', or 'z'), and
		 * dir is 0 if the wall is in the negative direction and 1 if it is in
		 * the positive direction.  Assumes that this is in the extreme
		 * direction of the coordinate, e.g. if w is WALL_TOP, the function
		 * assumes that this is in the far upward direction.
		 */
	/*void potentialNpcWallCollisions(vector<NpcWallPair> &cs,Wall w, char coord, int dir) {
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

					child->potentialNpcWallCollisions(cs, w, coord, dir);
				}
			}
		}
		else {
			//Add (npc, w) for all balls in this
			for (set<npc*>::iterator it = npcs.begin(); it != npcs.end();it++) 
			{
				npc* npc  = *it;
				NpcWallPair nwp;
				nwp.Npc = npc;
				nwp.wall = w;
				cs.push_back(nwp);
			}
		}
	}*/
public:
	//Constructs a new Octree.  c1 is (minX, minY, minZ), c2 is (maxX, maxY,
		//maxZ), and d is the depth, which starts at 1.
	Octree(vec3 c1, vec3 c2, int d, float size) 
	{
		BOX_SIZE = size;
		corner1 = c1;
		corner2 = c2;
		center.x = (c1.x + c2.x) / 2;
		center.y = (c1.y + c2.y) / 2;
		center.z = (c1.z + c2.z) / 2;
		depth = d;
		numNpcs = 0;
		hasChildren = false;
	}

	//Destructor
	~Octree() 
	{
		if (hasChildren) {
			destroyChildren();
		}
	}
	//Adds a npc to this
	void add(npc* Npc) 
	{
		numNpcs++;
		if (!hasChildren && depth < MAX_OCTREE_DEPTH && numNpcs > MAX_NPCS_PER_OCTREE) 
		{
			haveChildren();
		}
		if (hasChildren) {
			fileNpc(Npc, Npc->GetPosition(), true);
		}
		else {
			npcs.insert(Npc);
		}
	}

	//Removes a npc from this
	void remove(npc* Npc) {
		remove(Npc, Npc->GetPosition());
	}

	//Changes the position of a npc in this from oldPos to npc->position
	void NpcMoved(npc* Npc, vec3 oldPos) {
		remove(Npc, oldPos);
		add(Npc);
	}


	//Adds potential npc-npc collisions to the specified set
	void potentialNpcNpcCollisions(vector<NpcPair> &collisions) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 2; y++) {
					for (int z = 0; z < 2; z++) {
						children[x][y][z]->
							potentialNpcNpcCollisions(collisions);
					}
				}
			}
		}
		else {
			//Add all pairs (ball1, ball2) from balls
			for (set<npc*>::iterator it = npcs.begin(); it != npcs.end();
				it++) {
				npc* npc1 = *it;
				for (set<npc*>::iterator it2 = npcs.begin();it2 != npcs.end(); it2++) 
				{
					npc *npc2 = *it2;
					//This test makes sure that we only add each pair once
					if (npc1 < npc2) {
						NpcPair np;
						np.npc1 = npc1;
						np.npc2 = npc2;
						collisions.push_back(np);
					}
				}
			}
		}
	}
	//Adds all balls in this or one of its descendants to the specified set
	void collectNpcs(set<npc*> &ns) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 2; y++) {
					for (int z = 0; z < 2; z++) {
						children[x][y][z]->collectNpcs(ns);
					}
				}
			}
		}
		else {
			for (set<npc*>::iterator it = npcs.begin(); it != npcs.end();
				it++) {
				npc* Npc = *it;
				ns.insert(Npc);
			}
		}
	}
	//Returns whether two npcs are colliding
	bool testNpcNpcCollision(npc* n1, npc* n2) {
		//Check whether the npcs are close enough
		float r = n1->r + n2->r;
		if (length2(n1->GetPosition() - n2->GetPosition()) < r * r) {
			//Check whether the npcs are moving toward each other
			vec3 netVelocity = n1->GetVelocity() - n2->GetVelocity();
			vec3 displacement = n1->GetPosition() - n2->GetPosition();
			return dot(netVelocity,displacement) < 0;
		}
		else
			return false;
	}

	//Handles all Npc-Npc collisions
	void handleNpcNpcCollisions(vector<npc*> &npcs, Octree* octree) {
		vector<NpcPair> nps;
		potentialNpcNpcCollisions(nps, npcs, octree);
		for (unsigned int i = 0; i < nps.size(); i++) {
			NpcPair np = nps[i];

			npc* n1 = np.npc1;
			npc* n2 = np.npc2;
			if (testNpcNpcCollision(n1, n2)) {
				//Make the npcs reflect off of each other
				vec3 displacement = normalize((n1->GetPosition() - n2->GetPosition()));
				displacement.x = displacement.x *2;
				displacement.y = displacement.y * 2;
				displacement.z = displacement.z * 2;
				n1->velocity -=  displacement * dot(n1->velocity,displacement);
				n2->velocity -=  displacement * dot(n2->velocity,displacement);
			}
		}
	}
	//Returns whether a npc and a wall are colliding
	bool testBallWallCollision(npc* npc1, Wall wall) {
		vec3 dir = wallDirection(wall);
		//Check whether the npc is far enough in the "dir" direction, and whether
		//it is moving toward the wall 
		return dot(npc1->GetPosition(),dir) + npc1->r > BOX_SIZE / 2 &&
			dot(npc1->GetVelocity(),dir) > 0;
	}

	//Handles all Npc-wall collisions
	//void handleNpcWallCollisions(vector<npc*> &npcs, Octree* octree) {
	//	vector<NpcWallPair> nwps;
	//	potentialNpcWallCollisions(nwps, npcs, octree);
	//	for (unsigned int i = 0; i < nwps.size(); i++) {
	//		NpcWallPair nwp = nwps[i];
	//
	//		npc* n = nwp.Npc;
	//		Wall w = nwp.wall;
	//		if (testBallWallCollision(n, w)) {
	//			//Make the npc reflect off of the wall
	//			vec3 dir = normalize((wallDirection(w)));
	//			dir.x = dir.x * 2;
	//			dir.y = dir.y * 2;
	//			dir.z = dir.z * 2;
	//			n->velocity -=  dir * dot(n->velocity,dir);
	//		}
	//	}
	//}
	

	//Adds potential ball-wall collisions to the specified set
	//void potentialNpcWallCollisions(vector<NpcWallPair> &collisions) {
	//	potentialNpcWallCollisions(collisions, WALL_LEFT, 'x', 0);
	//	potentialNpcWallCollisions(collisions, WALL_RIGHT, 'x', 1);
	//	potentialNpcWallCollisions(collisions, WALL_BOTTOM, 'y', 0);
	//	potentialNpcWallCollisions(collisions, WALL_TOP, 'y', 1);
	//	potentialNpcWallCollisions(collisions, WALL_FAR, 'z', 0);
	//	potentialNpcWallCollisions(collisions, WALL_NEAR, 'z', 1);
	//}


//Puts potential ball-ball collisions in potentialCollisions.  It must return
//all actual collisions, but it need not return only actual collisions.
void potentialNpcNpcCollisions(vector<NpcPair> &potentialCollisions,
	vector<npc*> &balls, Octree* octree) 
{
	//Fast method
	octree->potentialNpcNpcCollisions(potentialCollisions);

	/*
	//Slow method
	for(unsigned int i = 0; i < balls.size(); i++) {
		for(unsigned int j = i + 1; j < balls.size(); j++) {
			BallPair bp;
			bp.ball1 = balls[i];
			bp.ball2 = balls[j];
			potentialCollisions.push_back(bp);
		}
	}
	*/
}

//Puts potential ball-wall collisions in potentialCollisions.  It must return
//all actual collisions, but it need not return only actual collisions.
//void potentialNpcWallCollisions(vector<NpcWallPair> &potentialCollisions,
	//vector<npc*> &npcs, Octree* octree) 
//{
	//Fast method
	//octree->potentialNpcWallCollisions(potentialCollisions);

	/*
	//Slow method
	Wall walls[] =
		{WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM};
	for(unsigned int i = 0; i < balls.size(); i++) {
		for(int j = 0; j < 6; j++) {
			BallWallPair bwp;
			bwp.ball = balls[i];
			bwp.wall = walls[j];
			potentialCollisions.push_back(bwp);
		}
	}
	*/
//}

	//Returns the direction from the origin to the wall
	vec3 wallDirection(Wall wall) {
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
	
};

	

	
	

	

	

	

	

	

	



















































