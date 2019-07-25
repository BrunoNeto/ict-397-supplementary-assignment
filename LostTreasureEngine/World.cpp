#include "World.h"



World::World()
{
	loadWorld();
	
	
}
void World::Init() 
{
	CTimer::GetInstance()->Initialize();
	// Create asset factory
	m_assetFactory = new GameAssetFactory();

	// Create NPC
	npc = m_assetFactory->CreateAsset(ASS_NPC, "NPC");
	npc->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	npc->SetPosition({ (t.getWorldSizeX()/2),80,(t.getWorldSizeZ() - 100)});
	npc->SetRotation({ 0,1,0 });
	npc->SetAnimation(RUN);
	m_assetFactory->AddAsset(npc);

	// Create Object
	object = m_assetFactory->CreateAsset(ASS_OBJECT, "Treasure");
	object->LoadFromFilePath("models/treasure_chest.md2", "models/treasure_chest.bmp");
	object->SetPosition(100, (t.getWorldSizeZ() - 80), t);
	object->SetScale(1.5);
	m_assetFactory->AddAsset(object);

	// Create Structure
	structure = m_assetFactory->CreateAsset(ASS_STRUCTURE, "House");
	structure->LoadFromFilePath("models/farmhouse.md2", "models/farmhouse.bmp");
	structure->SetPosition((t.getWorldSizeX() - 150), (t.getWorldSizeZ() - 80), t);
	structure->SetScale(4);
	m_assetFactory->AddAsset(structure);
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
	npc->Update(bAnimated ? time : 0.0, t);
	curt = time;
	elapsed = curt - last;

	last = curt;
	
}
void World::Draw() 
{
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	cam.Animate(bAnimated ? elapsed : 0.0, t);
	t.bruteForceRender();
	structure->Draw(time);
	object->Draw(time);
	npc->Draw(bAnimated ? time : 0.0);
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
