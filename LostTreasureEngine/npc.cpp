#include "npc.h"



npc::npc()
{
	
	initLookAt = vec3(0.0, 0.0, 1.0);
	position = vec3(0,0,0);
	velocity = vec3(0.0, 0.0, 0.01);
	acceleration = vec3(0.0, 0.0, 0.0);
	currentAnimation = 0;
	interactionMsg = "Hey there stranger";

	//Sets up the NPC stateMachine
	NPCSM = new stateMachine<npc>(this);
	NPCSM->setCurrentState(&wander_state::Instance());
	NPCSM->setGlobalState(&wander_state::Instance());
}

const void npc::Destroy()
{
	
	delete NPCSM;
}
npc::~npc()
{
	Destroy(); //removes the state machine completely
}
bool npc::Inbounds(Terrain&t) 
{
	if (position.x < 0 || position.x > t.getWorldSizeX())
	{
			return false;
	}
	else if (position.z < 0 && position.z > t.getWorldSizeZ())
	{
		return false;
	}
	else return true;
}
bool npc::onborder(Terrain&t)
{
	if (position.x <= 0 || position.z <=0)
	{
		return true;
	}
	else if (position.x >= t.getWorldSizeX() || position.z >= t.getWorldSizeZ())
	{
		return true;
	}
	else { return false; }
	
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
	return initLookAt;
}
vec3 npc::GetVelocity()
{
	return velocity;
}
vec3 npc::GetAcceleration()
{
	return acceleration;
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
void npc::SetPosition(float x, float z, Terrain& t) 
{
	position.x = x;
	position.z = z;
	position.y = t.getHeight(x, z);
}
void npc::LoadFromFilePath(const char * modelFileName, const char * modelSkinFileName)
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
	initLookAt = faci;
}
void npc::SetVelocity(vec3 v) 
{
	velocity = v;
}
void npc::SetAcceleration(vec3 a)
{
	acceleration = a;
}
void npc::SetAnimation(int animation)
{
	npcmodel.SetAnim(animation);
}
void npc::SetHeight(float y)
{
	position.y = y;
}
void npc::SetScale(float scale) 
{
	npcmodel.ScaleModel(scale);
}
//void SetState(){}
void npc::SetAnimIdle() 
{
	npcmodel.SetAnim(STAND);
}
void npc::SetAnimWalk() 
{
	npcmodel.SetAnim(RUN);
}

void npc::SetAnimWave()
{
	npcmodel.SetAnim(WAVE);
}
void npc::Interact() 
{
	cout << interactionMsg << endl;
}
void npc::LookAtPlayer(vec3 camPos) //use vector math to determine the new player facing
{
	vec3 newLookVec = camPos - position;
	rotationAngle = acos(dot(normalize(lookAt), normalize(newLookVec)));//theta=acos((v1 DOT v2)/(|v1|*|v2|))

}
float degToRad2(float value)
{
	float rad = value * 0.0175;
	return rad;
}
void npc::Move(float deltaTime, Terrain& t)
{
	if (rotationAngle > 0 || rotationAngle < 0)//if rotation is at an amount higher or less than 0 calculate new velocity
	{//update velocity vector with new heading
		velocity.x = (initLookAt.z*sin(degToRad2(rotationAngle)) + initLookAt.x*cos(degToRad2(rotationAngle)));
		velocity.z = (initLookAt.z*cos(degToRad2(rotationAngle)) - initLookAt.x*sin(degToRad2(rotationAngle)));
		
	}
	
	
	//velocity z-component
	// strafe speed is velocity x-component
	float strafeSpeed = velocity.x * deltaTime;
	float speed = velocity.z * deltaTime;
	
	

	// speed limit
	if (speed > 0.5)
	{
		speed = 0.5;
	}
		
	if (strafeSpeed > 0.5)
	{
		strafeSpeed = 0.5;
	}
		
	if (speed < -0.5)
	{
		speed = -0.5;
	}
		
	if (strafeSpeed < -0.5)
	{
		strafeSpeed = -0.5;
	}
		
	//if (speed > 0 || strafeSpeed > 0)
	//{
		//if (this->GetCurrentAnimation() != RUN)
		//{
		//	this->SetAnimWalk();
		//}
	//}
	//else
	//if (this->GetCurrentAnimation() != STAND)
		//{
		//	this->SetAnimIdle();
		//}
	// friction
	if (velocity.length() > 0.0)
		acceleration = -velocity * 1.0f;

	velocity += acceleration * deltaTime;
	// calculate new position of npc this part is working though in world coordinates not character may need to build rotation matrix and mvp for these calcs
	position.x += strafeSpeed;
	position.z += speed;
	NPCSM->executeState(this);
	if(!Inbounds(t)) 
	{
		NPCSM->exitState(this);
		NPCSM->enterState(this);
		NPCSM->executeState(this);
		
	}
	if (onborder(t))
	{
		NPCSM->exitState(this);
		NPCSM->enterState(this);
		NPCSM->executeState(this);
	}
	t.inWorld(position.x, position.z);//keeps npc within the border of terrain also working

	position.y = float(t.getHeight(position.x, position.z)) + 25;//to set y relative to the scaled height of terrain 	
	
}

void npc::Update(float deltaTime, Terrain& t)
{
	// this function will be used to update world positions and do state stuuf
	//NPCSM->update();
	Move(deltaTime, t);
	
	
	
}
void npc::Draw(float time)
{
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotationAngle, rotation.x, rotation.y, rotation.z);
	npcmodel.DrawModel(time);
	glPopMatrix();
	
	
	
	
}
