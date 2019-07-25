#include "Structure.h"

Structure::Structure()
{
	m_model = new MD2Model();
	position = vec3(0, 0, 0);
	rotation = vec3(1, 0, 0);
	angle = 0;	
}


Structure::~Structure()
{
}
vec3 Structure::GetPosition()
{
	return position;
}

vec3 Structure::GetRotation()
{
	return rotation;
}

float Structure::GetAngle()
{
	return angle;
}

void Structure::SetPosition(vec3 pos)
{
	// Do nothing in structure
}

void Structure::Update(float deltaTime, Terrain& t)
{
	// Do nothing in structure
}

void Structure::SetPosition(float x, float z, Terrain& t)
{
	position.x = x;
	position.z = z;
	position.y = t.getHeight(x, z);
}

void Structure::SetRotation(vec3 rot)
{
	rotation = rot;
}

void Structure::SetAngle(float a)
{
	angle = a;
}
void Structure::ScaleStructure(float scale)
{
	m_model->ScaleModel(scale);
}

void Structure::SetScale(float scale) 
{
	m_model->ScaleModel(scale);
}

void Structure::LoadStructureModel(const char* modelFileName, const char* modelSkinFileName)
{
	structureModel.LoadModel(modelFileName);
	structureModel.LoadSkin(modelSkinFileName);
}
void Structure::Draw(float time)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	m_model->DrawModel(time);
	glPopMatrix();
}

const void Structure::Destroy()
{
	// Todo: destroy all items of Object class
}

void Structure::LoadFromFilePath(const char * modelFileName, const char * modelSkinFileName)
{
	m_model->LoadModel(modelFileName);
	m_model->LoadSkin(modelSkinFileName);
}
