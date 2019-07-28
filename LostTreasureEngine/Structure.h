#pragma once
#include <glm/glm.hpp>
#include "md2.h"
#include "Terrain.h"
#include "IGameAsset.h"
using namespace std;
using namespace glm;
class World;
//
//	Structure.h - header file
//	@author Bruno Neto
//	@brief an  class for holding our building object holds a model and the structures needed for loading rendering 
//	version 1.0
class Structure : public IGameAsset
{
private:
	MD2Model structureModel;
	vec3 position;
	vec3 rotation;
	float angle;
	string m_filePath;
	float r = 5;
public:
	/**
	*	@brief Structure default constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	Structure();
	/**
	*	@brief Structure default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~Structure();
	/**
	*	@brief gets the position vector of Structure
	*   @see
	*	@param
	*	@return the position vector
	*	@pre
	*	@post
	*/
	vec3 GetPosition();
	/**
	*	@brief gets the rotation vector of Structure
	*   @see
	*	@param
	*	@return the rotation vector
	*	@pre
	*	@post
	*/
	vec3 GetRotation();
	/**
	*	@brief  function for inheritance purposes does nothing for object
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	void TriggerWander() {}
	
	/**
	*	@brief  function for inheritance purposes
	*   @see
	*	@param
	*	@return glm vec 3
	*	@pre
	*	@post
	*/
	vec3 GetVelocity() { return velocity; }
	
	/**
	*	@brief gets the rotation angle of Structure
	*   @see
	*	@param
	*	@return the rotation angle
	*	@pre
	*	@post
	*/
	float GetAngle();
	/**
	*	@brief deletes the Structure
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	virtual const void Destroy();
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
	* @brief Gets the file path
	*
	* Returns the file path containing the object information.
	*
	* @return std::string
	*/
	virtual const std::string& GetFilePath() const { return m_filePath; }

	/**
	* @brief Sets the file path
	*
	* Sets the file path containing the object information.
	*
	* @param std::string& filePath
	* @return void
	*/
	virtual void SetFilePath(const std::string& filePath) { m_filePath = filePath; }
	/**
	*	@brief sets the position of the Structure
	*   @see
	*	@param position the position vector of the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(vec3 pos);
	/**
	*	@brief sets the position vector for Structure
	*   @see
	*	@param rot the position vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(float x, float z, Terrain& t);
	/**
	*	@brief sets the rotation vector for Structure
	*   @see
	*	@param rot the rotation vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetRotation(vec3 rot);
	/**
	*	@brief sets the rotation angle for Structure
	*   @see
	*	@param angle to float to use for rotation angle
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAngle(float angle);
	/**
	*	@brief scales the structure model by the float given
	*   @see
	*	@param scale the float value to use as scaling factor
	*	@return void
	*	@pre
	*	@post
	*/
	void SetScale(float scale);
	/**
	*	@brief loads the modelfile and texture file to be used for structure's model, note that we will be using an md2 model with only 1 part
	*   @see
	*	@param modelFileName the name/address of the model file
	*	@param modelSkinFileName the name/address of the texture file
	*	@return void
	*	@pre modelFileName must point to a valid md2 model, modelSkinFilename must point to a valid 24bit bitmap file
	*	@post
	*/
	void LoadFromFilePath(const char* modelFilename, const char* modelSkinFilename);
	/**
	*	@brief draws the structure
	*   @see
	*	@param time variable used to determine frame to draw
	*	@return void
	*	@pre
	*	@post
	*/
	void Draw(float deltatime);
	/**
	*	@brief structure update , doesn't do anything at all included for inheritance prposes
	*   @see
	*	@param detlaTime the elapsed time since last update
	*	@param t the gameworld terrain being referenced for movement (used to getheight)
	*	@return void
	*	@pre
	*	@post
	*/
	void Update(float deltaTime, Terrain& t);
};

