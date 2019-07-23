#include "Item.h"



Item::Item()
{
	position=vec3(0,0,0);
	rotation=vec3(1,0,0);
	angle = 0;
	itemType = 0;//set to default
}


Item::~Item()
{
}
vec3 Item::GetPosition() 
{
	return position;
}

vec3 Item::GetRotation() 
{
	return rotation;
}

float Item::GetAngle() 
{
	return angle;
}

void Item::SetPosition(float x, float z, Terrain& t)
{
	position.x = x;
	position.z = z;
	position.y = t.getHeight(x, z);
}

void Item::SetRotation(vec3 rot) 
{
	rotation = rot;
}

void Item::SetAngle(float a) 
{
	angle = a;
}

int Item::TransferToPlayer() 
{
	return itemType;
}
void Item::ScaleItem(float scale)
{
	itemModel.ScaleModel(scale);
}
void Item::LoadItemModel(const char* modelFileName, const char* modelSkinFileName) 
{
	itemModel.LoadModel(modelFileName);
	itemModel.LoadSkin(modelSkinFileName);
}
void Item::Draw(float time) 
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	itemModel.DrawModel(time);
	glPopMatrix();
}