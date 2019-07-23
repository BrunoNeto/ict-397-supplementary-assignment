#pragma once
#include "npc.h"
#include <set>
#include <vector>
/*using namespace std;
//Our data structure for making collision detection faster
class Octree {
private:
	float minX;
	float minZ;
	float maxX;
	float maxZ;
	float centerX; //(minX + maxX) / 2
	float centerZ; //(minZ + maxZ) / 2
	const int MIN_NPCS_PER_QUADTREE = 2;
	const int MAX_QUADTREE_DEPTH = 6;

	const int MAX_NPCS_PER_QUADTREE = 5;

	/* The children of this, if this has any.  children[0][*] are the
	 * children with x coordinates ranging from minX to centerX.
	 * children[1][*] are the children with x coordinates ranging from
	 * centerX to maxX.  Similarly for the other dimension of the children
	 * array.
	 */
	/*Octree *children[2][2];
	//Whether this has children
	bool hasChildren;
	//The npcs in this, if this doesn't have any children
	set<npc*> npcs;
	//The depth of this in the tree
	int depth;
	//The number of guys in this, including those stored in its children
	int numGuys;

	//Adds a guy to or removes one from the children of this
	void fileNpc(npc* Npc, float x, float z, bool addNpc) {
		//Figure out in which child(ren) the guy belongs
		for (int xi = 0; xi < 2; xi++) {
			if (xi == 0) {
				if (x - Npc->r > centerX) {
					continue;
				}
			}
			else if (x + Npc->r < centerX) {
				continue;
			}

			for (int zi = 0; zi < 2; zi++) {
				if (zi == 0) {
					if (z - Npc->r > centerZ) {
						continue;
					}
				}
				else if (z + Npc->r < centerZ) {
					continue;
				}

				//Add or remove the guy
				if (addNpc) {
					children[xi][zi]->add(Npc);
				}
				else {
					children[xi][zi]->remove(Npc, x, z);
				}
			}
		}
	}

	//Creates children of this, and moves the npcs in this to the children
	void haveChildren() {
		for (int x = 0; x < 2; x++) {
			float minX2;
			float maxX2;
			if (x == 0) {
				minX2 = minX;
				maxX2 = centerX;
			}
			else {
				minX2 = centerX;
				maxX2 = maxX;
			}

			for (int z = 0; z < 2; z++) {
				float minZ2;
				float maxZ2;
				if (z == 0) {
					minZ2 = minZ;
					maxZ2 = centerZ;
				}
				else {
					minZ2 = centerZ;
					maxZ2 = maxZ;
				}

				children[x][z] = new Octree(minX2, maxX2, minZ2, maxZ2, (depth + 1));
			}
		}

		//Remove all guys from "guys" and add them to the new children
		for (set<npc*>::iterator it = npcs.begin(); it != npcs.end();
			it++) {
			npc* Npc = *it;
			fileNpc(Npc, Npc->GetPosition().x, Npc->GetPosition().z, true);
		}
		npcs.clear();

		hasChildren = true;
	}

	//Adds all npc in this or one of its descendants to the specified set
	void collectNpcs(set<npc*> &ns) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int z = 0; z < 2; z++) {
					children[x][z]->collectNpcs(ns);
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

	//Destroys the children of this, and moves all guys in its descendants
	//to the "guys" set
	void destroyChildren() {
		//Move all guys in descendants of this to the "guys" set
		collectNpcs(npcs);

		for (int x = 0; x < 2; x++) {
			for (int z = 0; z < 2; z++) {
				delete children[x][z];
			}
		}

		hasChildren = false;
	}

	//Removes the specified guy at the indicated position
	void remove(npc* Npc, float x, float z) {
		numNpcs--;

		if (hasChildren && numNpcs < MIN_NPCS_PER_QUADTREE) {
			destroyChildren();
		}

		if (hasChildren) {
			fileNpc(Npc, x, z, false);
		}
		else {
			npcs.erase(Npc);
		}
	}
public:
	//Constructs a new Quadtree.  d is the depth, which starts at 1.
	Octree(float minX1, float minZ1, float maxX1, float maxZ1, int d) {
		minX = minX1;
		minZ = minZ1;
		maxX = maxX1;
		maxZ = maxZ1;
		centerX = (minX + maxX) / 2;
		centerZ = (minZ + maxZ) / 2;

		depth = d;
		numNpcs = 0;
		hasChildren = false;
	}

	~Octree() {
		if (hasChildren) {
			destroyChildren();
		}
	}

	//Adds a guy to this
	void add(npc* anpc) {
		numNpcs++;
		if (!hasChildren && depth < MAX_QUADTREE_DEPTH &&
			numGuys > MAX_NPCS_PER_QUADTREE) {
			haveChildren();
		}

		if (hasChildren) {
			fileNpc(anpc, anpc->GetPosition().x, anpc->GetPosition().z, true);
		}
		else {
			npcs.insert(anpc);
		}
	}

	//Removes a guy from this
	void remove(Guy* guy) {
		remove(guy, guy->x(), guy->z());
	}

	//Changes the position of a guy in this from the specified position to
	//its current position
	void guyMoved(Guy* guy, float x, float z) {
		remove(guy, x, z);
		add(guy);
	}

	//Adds potential collisions to the specified set
	void potentialCollisions(vector<GuyPair> &collisions) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int z = 0; z < 2; z++) {
					children[x][z]->potentialCollisions(collisions);
				}
			}
		}
		else {
			//Add all pairs (guy1, guy2) from guys
			for (set<Guy*>::iterator it = guys.begin(); it != guys.end();
				it++) {
				Guy* guy1 = *it;
				for (set<Guy*>::iterator it2 = guys.begin();
					it2 != guys.end(); it2++) {
					Guy* guy2 = *it2;
					//This test makes sure that we only add each pair once
					if (guy1 < guy2) {
						GuyPair gp;
						gp.guy1 = guy1;
						gp.guy2 = guy2;
						collisions.push_back(gp);
					}
				}
			}
		}
	}
};*/
