#pragma once
#include <glm/glm.hpp>
#include "md2.h"
#include "Terrain.h"
using namespace std;
using namespace glm;
class World;
//
//	Item.h - header file
//	@author Bruno Neto
//	@brief an  class for holding our item object holds a model and the structures needed for loading rendering 
//	version 1.0
class Item
{
private:
	MD2Model itemModel;
	vec3 position;
	vec3 rotation;
	float angle;
	int itemType;
public:
	/**
	*	@brief Item default constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	Item();
	/**
	*	@brief item default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~Item();
	/**
	*	@brief gets the position vector of item
	*   @see
	*	@param
	*	@return the position vector
	*	@pre
	*	@post
	*/
	vec3 GetPosition();
	/**
	*	@brief gets the rotation vector of item
	*   @see
	*	@param
	*	@return the rotation vector
	*	@pre
	*	@post
	*/
	vec3 GetRotation();
	/**
	*	@brief gets the rotation angle of item
	*   @see
	*	@param
	*	@return the rotation angle
	*	@pre
	*	@post
	*/
	float GetAngle();
	
	/**
	*	@brief scales the item model by the float given
	*   @see
	*	@param scale the float value to use as scaling factor
	*	@return void
	*	@pre
	*	@post
	*/
	void ScaleItem(float scale);
	/**
	*	@brief sets the position vector for item
	*   @see
	*	@param rot the position vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(float x, float z, Terrain& gameWorld);
	/**
	*	@brief sets the rotation vector for item
	*   @see
	*	@param rot the rotation vector
	*	@return void
	*	@pre
	*	@post
	*/

	void SetRotation(vec3 rot);
	/**
	*	@brief sets the rotation angle for item
	*   @see
	*	@param angle to float to use for rotation angle
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAngle(float angle);
	/**
	*	@brief function for transferring item to player(will trigger when player collides with item)
	*   @see
	*	@param 
	*	@return the int value for itemtype
	*	@pre
	*	@post
	*/
	int TransferToPlayer();

	void LoadItemModel(const char* modelFilename, const char* modelSkinFilename);
	void Draw(float deltatime);

};

