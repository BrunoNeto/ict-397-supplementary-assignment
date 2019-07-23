#pragma once

#include "IGameAsset.h"
#include "md2.h"

/*
* @class Object
* @brief Object asset (static/dynamic)
*
* This class is used to store all the data about an Object. It inherits from
* the base class IGameAsset and allows for initialisation and drawing of
* the object.
*
* @note Currently not entirely implemented.
*
* @author Michael Bell
*/
class Object : public IGameAsset
{
public:
	/**
	* @brief Default constructor
	*
	* Empty default constructor.
	*
	* @return null
	*/
	Object() { }

	/**
	* @brief Destructor
	*
	* Empty destructor.
	*
	* @return null
	*/
	~Object() { Destroy(); }

	/**
	* @brief Parameter constructor
	*
	* Takes the parameter string asset name and creates a new
	* Object with that name identifier. Initialises the model of the
	* obejct as well.
	*
	* @param std::string assetName
	* @return null
	*/
	Object(std::string assetName);

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

	void SetPosition(vec3 position);
	/**
	*	@brief sets the facing of the npc
	*   @see
	*	@param facing the front facing vector of the model
	*	@return void
	*	@pre
	*	@post
	*/

	void SetPosition(float x, float z, Terrain& t);

	void SetRotation(vec3 rot);
	/**
	*	@brief sets the height of the npc to the value given
	*   @see
	*	@param y the value to set the height to
	*	@return void
	*	@pre
	*	@post
	*/

	void SetScale(float scale);

	void Update(float deltaTime, Terrain& t);

	void Draw(float time);

protected:
	/// Stores the file path containing the data
	std::string m_filePath;
	/// Model object
	MD2Model* m_model;
	vec3 position;	//position of the object
	vec3 rotation;	//vector for storing which axis to rotate in
	float angle;
	int itemType;
};