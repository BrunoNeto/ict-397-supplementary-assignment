#include "World.h"



World::World()
{
	loadWorld();
	BOX_SIZE = t.getWorldSizeX();
	_octree = new Octree(vec3({ 0, 0, 0 }), vec3({ BOX_SIZE, BOX_SIZE, BOX_SIZE}), 3, BOX_SIZE);

}
void World::Init() 
{
	//load all players and objects
	CTimer::GetInstance()->Initialize();
	// Create asset factory
	m_assetFactory = new GameAssetFactory();
	int numofnpcs = 25;//number of npcs to be set from script
	
	for (int i = 0; i < numofnpcs; i++)
	{
		
		CTimer::GetInstance()->Update();
		time = CTimer::GetInstance()->GetTimeMSec();
		srand(time);
		float x = rand();
		float y;
		CTimer::GetInstance()->Update();
		time = CTimer::GetInstance()->GetTimeMSec()+i ;
		srand(time);
		float z = rand();
		if (x < 0)
		{
			x = 0+i;
		}
		if (x > BOX_SIZE)
		{
			x = BOX_SIZE-i;
		}
		if (z < 0) { z = 0+i; }
		if (z > BOX_SIZE) { z = BOX_SIZE-i; }
		y = t.getHeight(x, z);

		// Create NPC with factory
		npc1 = m_assetFactory->CreateAsset(ASS_NPC, "NPC");
		npc1->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
		npc1->SetPosition({ x,y,z });
		npc1->SetRotation({ 0,1,0 });
		npc1->SetAnimation(RUN);
		m_assetFactory->AddAsset(npc1);
		_igameassets.push_back(npc1);
		_octree->add(npc1);
		
	}
	// Create Object
	object = m_assetFactory->CreateAsset(ASS_OBJECT, "Treasure");
	object->LoadFromFilePath("models/treasure_chest.md2", "models/treasure_chest.bmp");
	object->SetPosition(100, (t.getWorldSizeZ() - 80), t);
	object->SetScale(1.5);
	m_assetFactory->AddAsset(object);
	_igameassets.push_back(object);
	_octree->add(object);
	// Create Structure
	structure = m_assetFactory->CreateAsset(ASS_STRUCTURE, "House");
	structure->LoadFromFilePath("models/farmhouse.md2", "models/farmhouse.bmp");
	structure->SetPosition((t.getWorldSizeX() - 150), (t.getWorldSizeZ() - 80), t);
	structure->SetScale(4);
	m_assetFactory->AddAsset(structure);
	_igameassets.push_back(structure);
	_octree->add(structure);
}

World::~World()
{
	
	unLoadWorld();
	cleanup();
}
void World::unLoadWorld() 
{
	t.unLoadHeightField();
	
}
void World::cleanup()
{
	for (unsigned int i = 0; i < _igameassets.size(); i++) {
		delete _igameassets[i];
	}
	delete _octree;
}
bool World::loadWorld()
{
	t.setScalingFactor(10.0, 0.3, 10.0);
	string filename = "height128.raw";
	int filesize = 128;
	
	t.LoadHeightField(filename, filesize);
	
	
	
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
	//get time
	CTimer::GetInstance()->Update();
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	// cycle through octree updating all assets that need updating
	for (unsigned int i = 0; i < _igameassets.size(); i++)
	{
		_igameassets[i]->Update(bAnimated ? time : 0.0, t);
		
	}
	
	// cycle through octree handling collisions
	_octree->handleIGameAssetIGameAssetCollisions(_igameassets,_octree);
	// get elapsed time needed for the camera which runs of since last update rather than runtime
	curt = time;
	elapsed = curt - last;

	last = curt;
	
}
void World::Draw()
{
	CTimer::GetInstance()->Update();
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	cam.Animate(bAnimated ? elapsed : 0.0, t);
	t.bruteForceRender();
	
	//Draw the assets
	for (unsigned int i = 0; i < _igameassets.size(); i++) 
	{
		 _igameassets[i]->Draw(bAnimated ? time : 0.0);
	}
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
