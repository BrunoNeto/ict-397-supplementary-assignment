#pragma once

#include "md2.h"
#include <glm/glm.hpp>
#include <string>
#include "World.h"
#include "IGameAsset.h"
using namespace std;
using namespace glm;
//
//	npc.h - header file
//	@author Bruno Neto
//	@brief an  class for holding our npc object holds a model and the structures needed for loading rendering and animating
//	version 1.0
class npc : public IGameAsset
{
private:
	MD2Model* npcmodel;//the actual model data of the npc
	vec3 position;//position of the npc in the world
	vec3 rotation;//vector for storing which axis to rotate in
	float rotationAngle;// the angle to rotate by
	vec3 lookAt;//the vecor for direction the npc is facing
	
	vec3 acceleration;		// acceleration of npc
	int currentAnimation;//the animation currently set on the md2 model
	string interactionMsg;//the current set interaction message of the npc
	//state will be a variable
public:
	npc();//takes a filename for a model and a skin and loads the model and sets other varables to defaults
	~npc();
	void SetAnimIdle();
	void SetAnimWalk();
	void SetAnimWave();
	void Interact();
	void LookAtPlayer(vec3 campos);
	void Move(float deltaTime, World& gameworld);
	vec3 velocity;

	//MD2Model GetModel();
	MD2Model* GetModel() { return npcmodel; }
	vec3 GetPosition();
	vec3 GetFacing();
	vec3 GetAcceleration();
	vec3 GetVelocity();
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
	void SetAcceleration(vec3 a);
	void SetVelocity(vec3 v);
	void SetAnimation(int);
	void ScaleNPC(float scale);
	//void SetState();
	void Update(float deltaTime, World& gameWorld);
	void Draw(float time);

	/**
		* @brief Loads an NPC from file
		*
		* Takes the parameter string file path and loads the NPC data into the
		* corresponding model member variable.
		*
		* @param std::string filePath
		* @return void
		*/
	virtual void LoadFromFilePath(const char *filename);

	virtual const void Destroy();

	/**
	* @brief Gets the file path
	*
	* Returns the file path containing the NPC information.
	*
	* @return std::string
	*/
	virtual const std::string & GetFilePath() const;

	/**
	* @brief Sets the file path
	*
	* Sets the file path containing the NPC information.
	*
	* @param std::string& filePath
	* @return void
	*/
	virtual void SetFilePath(const std::string& filePath);

	virtual void SetCamera(CCamera* camera) { npcmodel->SetCamera(camera); }

	virtual void SetScale(glm::vec3 scale) { npcmodel->SetScale(scale); }

	virtual void AddTexutre(GLuint textureId, std::string textureFilePath) { }


};

