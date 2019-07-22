#include "Structure.h"

Structure::Structure()
{
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

void Structure::SetPosition(float x, float z, World& gameWorld)
{
	position.x = x;
	position.z = z;
	position.y = gameWorld.getHeight(x, z);
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
	structureModel.ScaleModel(scale);
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
	structureModel.DrawModel(time);
	glPopMatrix();
}
