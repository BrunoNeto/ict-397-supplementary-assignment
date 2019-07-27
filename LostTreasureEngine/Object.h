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
	float r = 1;
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
	/**
	* @brief the destructor for object/item class
	* @param 
	* @return void
	*/
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
	/**
	*	@brief sets the position of the object
	*   @see
	*	@param position the position vector of the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(vec3 position);
	
	/**
	*	@brief sets the position of the object
	*   @see
	*	@param float x the x position
	*	@param float z the z position
	*	@param Terrain t the terrain used for getting height
	*	@return void
	*	@pre
	*	@post
	*/
	void SetPosition(float x, float z, Terrain& t);
	/**
	*	@brief sets the rotaion of the npc to the value given
	*   @see
	*	@param glm::vec3 rot the value to set rotation to
	*	@return void
	*	@pre
	*	@post
	*/
	void SetRotation(vec3 rot);
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
	vec3 GetPosition() { return position; }

	/**
	*	@brief sets the scale of the npc to the value given
	*   @see
	*	@param float scale the value to set scale to
	*	@return void
	*	@pre
	*	@post
	*/
	void SetScale(float scale);
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
	/**
	*	@brief draws the npc
	*   @see
	*	@param time the value to use for time
	*	@return void
	*	@pre
	*	@post
	*/
	void Draw(float time);
	/**
	*	@brief sets the animation of the model stored within npc
	*   @see
	*	@param animEnumeration an int corresponding to one of the stored animations in the model
	*	@return void
	*	@pre
	*	@post
	*/
	void SetAnimation(int animEnumeration); 
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