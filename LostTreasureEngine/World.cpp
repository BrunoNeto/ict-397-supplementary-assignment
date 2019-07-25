#include "World.h"



World::World()
{
	loadWorld();
	
	t.getWorldSizeX();
}
void World::Init() 
{
	CTimer::GetInstance()->Initialize();

		npc* npc1 = new npc();
		npc1->SetModel("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
		npc1->SetAnimation(RUN);
		npc1->SetPosition({ (t.getWorldSizeX() / 2),300,(t.getWorldSizeZ() - 200) });
		npc1->SetRotation({ 0,1,0 });
		
		_npcs.push_back(npc1);
		_octree.add(npc1);

	
	
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
Terrain World::GetTerrain() { return t; }
World::~World()
{
	
	unLoadWorld();
}
void World::CleanUp() {
	for (unsigned int i = 0; i < _npcs.size(); i++) {
		delete _npcs[i];
	}
	
}
void World::unLoadWorld() 
{
	t.unLoadHeightField();
	CleanUp();
}
bool World::loadWorld()
{
	t.setScalingFactor(10.0, 0.4, 10.0);
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
	curt = time;
	elapsed = curt - last;
	mynpc.Update(bAnimated ? time:0.0, t);// updates a skele out of tree
	
		for (unsigned int i = 0; i < _npcs.size(); i++) 
		{//updates all the skeles in tree
			npc* Npc = _npcs[i];
			Npc->Update(bAnimated ? time : 0.0, t);
		}
		
		for (unsigned int i = 0; i < _npcs.size(); i++)
		{//updates all the skeles in tree
			_octree.handleNpcNpcCollisions(_npcs, &_octree);
			//_octree.handleNpcWallCollisions(_npcs, &_octree);
		}

	
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
	//if (_npcs.size() > 0) {
		for (unsigned int i = 0; i < _npcs.size(); i++) {
			
			npc* Npc = _npcs[i];
			Npc->Draw(bAnimated ? time:0.0);
		}
	//}
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














