#pragma once
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>

using namespace std;

class Terrain
{

public:
	Terrain();
	~Terrain();

	bool loadHeightfield(string filename, const int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
	void BruteForceRender();
	float getHeight(int xpos, int zpos);
	unsigned char getHeightColour(int xpos, int zpos);

protected:
	unsigned char *terrainData; //Data of the heightfield
	float scaleX; //how much you want to scale the terrain by
	float scaleY;
	float scaleZ;

private:
	int size; //the size of the heightfield along x and z - power of 2
};

