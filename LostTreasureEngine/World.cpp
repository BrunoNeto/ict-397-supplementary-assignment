#include "World.h"



World::World()
{
	loadWorld();
	
}


World::~World()
{
	
	unLoadWorld();
}
void World::unLoadWorld() 
{
	t.unLoadHeightField();
	
}
bool World::loadWorld()
{
	t.setScalingFactor(5.0, 0.25, 5.0);
	string filename = "height128.raw";
	int filesize = 128;
	
	//t.genFaultFormation(64, 128, 0, 255, 0.2f, false);
	t.LoadHeightField(filename, filesize);
	//load all players and objects
	return true;
}
int World::getWorldSize()
{
	int size = t.getSize();
	return size;
}
float World::inWorld(float& x, float& z)
{
	if (x < 0)
	{
		x = 0;
		return false;
	}
	else if (x > t.getSize())
	{
		x = (float)t.getSize();
		return false;
	}
	if (z < 0)
	{
		z = 0;
		return false;
	}
	else if (z > t.getSize())
	{
		z = (float)t.getSize();
		return false;
	}
	return true;
}
float World::getScaledHeight(float x, float z) 
{
	float y = (float)t.getHeight(x, z);
	return y;
}
bool World::loadWorldTexture() 
{
	t.LoadTexture();
	return true;
}

float World::getWorldXZHeight(float xpos, float zpos)
{
	float y = (float)t.getUnscaledHeight(xpos, zpos);
	return y;
}
void World::Render() 
{
	
	t.bruteForceRender();
	glutSwapBuffers();
}