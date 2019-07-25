#include "World.h"



World::World()
{
	loadWorld();
	BOX_SIZE = t.getWorldSizeX();
	_octree = new Octree(vec3({ 0, 0, 0 }), vec3({ BOX_SIZE, BOX_SIZE, BOX_SIZE}), 1, BOX_SIZE);

}
void World::Init() 
{
	CTimer::GetInstance()->Initialize();
	// Create asset factory
	m_assetFactory = new GameAssetFactory();

	// Create NPC
	npc1 = m_assetFactory->CreateAsset(ASS_NPC, "NPC");
	npc1->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	npc1->SetPosition({ (t.getWorldSizeX()/2),80,(t.getWorldSizeZ() - 100)});
	npc1->SetRotation({ 0,1,0 });
	npc1->SetAnimation(RUN);
	m_assetFactory->AddAsset(npc1);
	npc* n1 = new npc();
	n1->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	n1->SetPosition({ (t.getWorldSizeX() ),80,(t.getWorldSizeZ() - 80) });
	n1->SetRotation({ 0,1,0 });
	n1->SetAnimation(RUN);
	npc* n2 = new npc();
	n2->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	n2->SetPosition({ (t.getWorldSizeX() / 2),80,(t.getWorldSizeZ() - 100) });
	n2->SetRotation({ 0,1,0 });
	n2->SetAnimation(RUN);
	npc* n3 = new npc();
	n3->LoadFromFilePath("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	n3->SetPosition({ (t.getWorldSizeX()/3 ),80,(t.getWorldSizeZ() - 50) });
	n3->SetRotation({ 0,1,0 });
	n3->SetAnimation(RUN);


	_npcs.push_back(n1);
	_npcs.push_back(n2);
	_npcs.push_back(n3);
	_octree->add(n1);
	_octree->add(n2);
	_octree->add(n3);


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
	cleanup();
}
void World::unLoadWorld() 
{
	t.unLoadHeightField();
	
}
void World::cleanup()
{
	for (unsigned int i = 0; i < _npcs.size(); i++) {
		delete _npcs[i];
	}
	delete _octree;
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
	//CTimer::GetInstance()->Update();
	time = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	//npc1->Update(bAnimated ? time : 0.0, t);
	//std::multimap<std::string, IGameAsset*> _assets = m_assetFactory->GetAssets();
	//for (unsigned int i = 0; i < _assets.size(); i++)
	//{
		//_assets[i]->Update(bAnimated ? time : 0.0, t);
		//m_assetFactory->GetAssets()[i]
		//npc1->Update(bAnimated ? time : 0.0, t);
	//}
	for (unsigned int i = 0; i < _npcs.size(); i++)
	{
		_npcs[i]->Update(bAnimated ? time : 0.0, t);
		//npc3->Update(bAnimated ? elapsed : 0.0, t);
	}
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
	//for (unsigned int i = 0; i < m_assetFactory->GetAssets().size(); i++)
	//{
	//	npc1->Update(bAnimated ? time : 0.0, t);
	//}
	//npc1->Draw(bAnimated ? time : 0.0);
	//Draw the balls
	for (unsigned int i = 0; i < _npcs.size(); i++) 
	{
		 _npcs[i]->Draw(bAnimated ? time : 0.0);
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
