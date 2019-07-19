#include "npc.h"



npc::npc()
{
	position = {0,0,0};
	facing = {0,0,0};
	speed = 5;
	currentAnimation = 0;
	interactionMsg = "Hey there stranger";
}


npc::~npc()
{
	
}

MD2Model npc::GetModel() 
{
	return npcmodel;
}

vec3 npc::GetPosition() 
{
	return position;
}
vec3 npc::GetFacing() 
{
	return facing;
}
int npc::GetSpeed() 
{
	return speed;
}
int npc::GetCurrentAnimation() 
{
	return currentAnimation;
}
string npc::GetInteractionMsg() 
{
	return interactionMsg;
}
vec3 npc::GetRotation()
{
	return rotation;
}

void npc::SetRotation(vec3 rot) 
{
	rotation = rot;
}

float npc::GetRotationAngle()
{
	return rotationAngle;
}

void npc::SetRotationAngle(float rot)
{
	rotationAngle = rot;
}
//State GetState(){}
void npc::SetModel(const char * modelFileName, const char * modelSkinFileName)
{
	npcmodel.LoadModel(modelFileName);
	npcmodel.LoadSkin(modelSkinFileName);
}
void npc::SetPosition(vec3 pos) 
{
	position = pos;
}
void npc::SetFacing(vec3 faci) 
{
	facing = faci;
}
void npc::SetSpeed(int s) 
{
	speed = s;
}
void npc::SetAnimation(int animation)
{
	npcmodel.SetAnim(animation);
}
void npc::SetHeight(float y)
{
	position.y = y;
}
void npc::ScaleNPC(float scale) 
{
	npcmodel.ScaleModel(scale);
}
//void SetState(){}
void npc::Update(float y) 
{
	SetHeight(y+25);
	// this function will be used to update world positions and do state stuuf
}
void npc::Draw(float time) 
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotationAngle, rotation.x, rotation.y, rotation.z);
	npcmodel.DrawModel(time);
	glPopMatrix();
	
	
}
