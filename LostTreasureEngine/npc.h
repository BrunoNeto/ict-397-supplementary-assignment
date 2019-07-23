#pragma once

#include "md2.h"
#include <glm/glm.hpp>
#include <string>
#include "Terrain.h"

#include "state.h"
#include "stateMachine.h"
#include "NPCStates.h"

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
	vec3 lookAt;//the vecor for direction the npc is facing
	
	vec3 acceleration;		// acceleration of npc
	int currentAnimation;//the animation currently set on the md2 model
	string interactionMsg;//the current set interaction message of the npc
	//state will be a variable

	stateMachine<npc>* NPCSM; //ADDED FOR STATE
	
	
public:
	/**
	*	@brief npc default constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	npc();
	/**
	*	@brief npc default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~npc();
	/**
	*	@brief sets the model animation to stand /idle
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAnimIdle();
	/**
	*	@brief sets the model animation to running/walk
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAnimWalk();
	/**
	*	@brief sets the model animation to wave used in interaction
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAnimWave();
	/**
	*	@brief function to send stored npc interaction msg to the hud
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void Interact();
	/**
	*	@brief turns the npc to face the player/cam
	*   @see
	*	@param campos the position of the player/cam
	*	@return void
	*	@pre
	*	@post
	*/
	void LookAtPlayer(vec3 campos);
	/**
	*	@brief calculates movement in game using time and gameworld for the equations
	*   @see
	*	@param deltaTime the amount of time since last move
	*	@param gameworld reference to the gameworld
	*	@return void
	*	@pre
	*	@post
	*/
	void Move(float deltaTime, Terrain& gameworld);
	vec3 velocity;
	/**
	*	@brief gets the npc model
	*   @see
	*	@param
	*	@return the npc model
	*	@pre
	*	@post
	*/
	MD2Model GetModel();
	/**
	*	@brief gets the npc position vector
	*   @see
	*	@param
	*	@return the npc position vector
	*	@pre
	*	@post
	*/
	vec3 GetPosition();
	/**
	*	@brief gets the npc facing vector
	*   @see
	*	@param
	*	@return the npc facing vector
	*	@pre
	*	@post
	*/
	vec3 GetFacing();
	/**
	*	@brief gets the npc acceleration vector
	*   @see
	*	@param
	*	@return the npc acceleration vector
	*	@pre
	*	@post
	*/
	vec3 GetAcceleration();
	/**
	*	@brief gets the npc velocity vector
	*   @see
	*	@param
	*	@return the npc velocity vector
	*	@pre
	*	@post
	*/
	vec3 GetVelocity();
	/**
	*	@brief gets the npc current animation 
	*   @see
	*	@param
	*	@return the npc current animation 
	*	@pre
	*	@post
	*/
	int GetCurrentAnimation();
	/**
	*	@brief gets the npc interaction msg
	*   @see
	*	@param
	*	@return the interaction msg string
	*	@pre
	*	@post
	*/
	string GetInteractionMsg();
	/**
	*	@brief gets the rotation vector for the npc
	*   @see
	*	@param
	*	@return the rotation vector to be set on npc as a float
	*	@pre
	*	@post
	*
	*/
	vec3 GetRotation();
	/**
	*	@brief gets the rotation angle for the npc
	*   @see
	*	@param 
	*	@return the rotation angle to be set on npc as a float
	*	@pre
	*	@post
	*
	*/
	float GetRotationAngle();
	/**
	*	@brief sets the rotation angle for the npc
	*   @see
	*	@param rot the rotation angle to be set on npc
	*	@return void
	*	@pre
	*	@post
	*/
	void SetRotationAngle(float rot);
	//State GetState();
	/**
	*	@brief sets the rotation vector for the npc
	*   @see
	*	@param rot the rotation vector to be set on npc
	*	@return void
	*	@pre
	*	@post
	*/
	void SetRotation(vec3 rot);
	/**
	*	@brief sets the height of the npc to the value given
	*   @see
	*	@param y the value to set the height to
	*	@return void
	*	@pre
	*	@post
	*/
	void SetHeight(float y);
	/**
	*	@brief loads the modelfile and texture file to be used for npc's model, note that we will be using an md2 model with only 1 part
	*   @see
	*	@param modelFileName the name/address of the model file
	*	@param modelSkinFileName the name/address of the texture file
	*	@return void
	*	@pre modelFileName must point to a valid md2 model, modelSkinFilename must point to a valid 24bit bitmap file 
	*	@post
	*/
	void SetModel(const char* modelFileName, const char* modelSkinFilename);
	/**
	*	@brief sets the position of the npc
	*   @see
	*	@param position the position vector of the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(vec3 position);
	/**
	*	@brief sets the facing of the npc
	*   @see
	*	@param facing the front facing vector of the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetFacing(vec3 facing);
	/**
	*	@brief sets npc acceleration vector
	*   @see
	*	@param a the new value for the acceleration vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAcceleration(vec3 a);
	/**
	*	@brief sets npc velocity vector
	*   @see
	*	@param v the new value for the velocity vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetVelocity(vec3 v);
	/**
	*	@brief sets the animation of the model stored within npc
	*   @see
	*	@param animEnumeration an int corresponding to one of the stored animations in the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAnimation(int animEnumeration);
	/**
	*	@brief scales the npc model by the float given
	*   @see
	*	@param scale the float value to use as scaling factor
	*	@return void
	*	@pre
	*	@post
	*/
	void ScaleNPC(float scale);
	//void SetState();
	/**
	*	@brief npc update , processes movement using time and gameworld reference, 
	*	this will likely change when i move npc into world as it will not need world variable to be passed in
	*   @see
	*	@param detlaTime the elapsed time since last update
	*	@param gameworld the gameworld being referenced for movement (used to getheight)
	*	@return void
	*	@pre
	*	@post
	*/
	void Update(float deltaTime, Terrain& gameWorld);
	/**
	*	@brief draws the npc
	*   @see
	*	@param time variable used to determine frame to draw
	*	@return void
	*	@pre
	*	@post
	*/
	void Draw(float time);
};

