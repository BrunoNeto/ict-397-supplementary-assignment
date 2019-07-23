#include "World.h"



World::World()
{
	loadWorld();
	
	
}
void World::Init() 
{
	CTimer::GetInstance()->Initialize();
	mynpc.SetModel("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	mynpc.SetAnimation(RUN);
	mynpc.SetPosition({ (t.getWorldSizeX() / 2),300,(t.getWorldSizeZ() - 100) });
	mynpc.SetRotation({ 0,1,0 });
	treasure.LoadItemModel("models/treasure_chest.md2", "models/treasure_chest.bmp");
	treasure.SetPosition(100, (t.getWorldSizeZ() - 80), t);

	building.LoadStructureModel("models/farmhouse.md2", "models/farmhouse.bmp");
	building.SetPosition((t.getWorldSizeX() - 150), (t.getWorldSizeZ() - 80), t);
	building.ScaleStructure(4);
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
	t.setScalingFactor(5.0, 0.3, 5.0);
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
	else if (x > getWorldSizeX())
	{
		x = getWorldSizeX();
		return false;
	}
	if (z < 0)
	{
		z = 0;
		return false;
	}
	else if (z > getWorldSizeZ())
	{
		z = getWorldSizeZ();
		return false;
	}
	return true;
}
float World::getHeight(float x, float z) 
{
	float y = t.getHeight(x, z);
	return y;
}
bool World::loadWorldTexture() 
{
	t.LoadTexture();
	return true;
}

float World::getScaleY() {
	float scaleY =t.getScaleY();
	return scaleY;
}
float World::getWorldSizeX()
{
	return float(t.getSize()*t.getScaleX());
}

float World::getWorldSizeZ()
{
	return float(t.getSize()*t.getScaleZ());
}
float World::getWorldXZHeight(float xpos, float zpos)
{
	float y = (float)t.getUnscaledHeight(xpos, zpos);
	return y;
}
void World::Update() 
{
	CTimer::GetInstance()->Update();
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	mynpc.Update(bAnimated ? time:0.0, t);
	curt = time;
	elapsed = curt - last;

	last = curt;
	
}
void World::Draw() 
{
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	cam.Animate(bAnimated ? elapsed : 0.0, t);
	t.bruteForceRender();
	building.Draw(time);
	treasure.Draw(time);
	mynpc.Draw(bAnimated ? time:0.0);
	glutSwapBuffers();
}
void World::PauseWorld()
{
	if (bAnimated)
	{
		bAnimated = false;
	}
	else
	{
		bAnimated = true;
	}
}

CCamera* World::GetCam() 
{
	return &cam;
}