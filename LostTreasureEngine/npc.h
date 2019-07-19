#pragma once

#include "md2.h"
#include <glm/glm.hpp>
#include <string>
using namespace std;
using namespace glm;
//
//	npc.h - header file
//	@author Bruno Neto
//	@brief an  class for holding our npc object holds a model and the structures needed for loading rendering and animating
//	version 1.0
class npc
{
private:
	MD2Model npcmodel;//the actual model data of the npc
	vec3 position;//position of the npc in the world
	vec3 rotation;//vector for storing which axis to rotate in
	float rotationAngle;// the angle to rotate by
	vec3 facing;//the vecor for direction the npc is facing
	int speed;//the speed of the npc character for moving around the world
	int currentAnimation;//the animation currently set on the md2 model
	string interactionMsg;//the current set interaction message of the npc
	//state will be a variable
public:
	npc();//takes a filename for a model and a skin and loads the model and sets other varables to defaults
	~npc();
	MD2Model GetModel();
	vec3 GetPosition();
	vec3 GetFacing();
	int GetSpeed();
	int GetCurrentAnimation();
	string GetInteractionMsg();
	vec3 GetRotation();
	float GetRotationAngle();
	void SetRotationAngle(float rot);
	//State GetState();
	void SetRotation(vec3 rot);
	void SetHeight(float y);
	void SetModel(const char* modelFileName, const char* modelSkinFilename);
	void SetPosition(vec3 position);
	void SetFacing(vec3 facing);
	void SetSpeed(int speed);
	void SetAnimation(int);
	void ScaleNPC(float scale);
	//void SetState();
	void Update(float y);
	void Draw(float time);
};

