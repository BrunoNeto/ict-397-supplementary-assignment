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
//	@brief an  class for holding our item object holds a model and the structures needed for loading rendering 
//	version 1.0
class Structure
{
private:
	MD2Model structureModel;
	vec3 position;
	vec3 rotation;
	float angle;
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
	*	@brief gets the rotation angle of Structure
	*   @see
	*	@param
	*	@return the rotation angle
	*	@pre
	*	@post
	*/
	float GetAngle();
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

	/**
	* @brief Loads an object from file
	*
	* Takes the parameter string file path and loads the NPC data into the
	* corresponding model member variable.
	*
	* @param std::string filePath
	* @return void
	*/
	virtual void LoadFromFilePath(const char * modelFileName, const char * modelSkinFileName);

	virtual const void Destroy();

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

	void ScaleStructure(float scale);
	virtual void SetScale(float scale);
	void LoadStructureModel(const char* modelFilename, const char* modelSkinFilename);
	void Draw(float deltatime);


	protected:
		/// Stores the file path containing the data
		std::string m_filePath;
};

