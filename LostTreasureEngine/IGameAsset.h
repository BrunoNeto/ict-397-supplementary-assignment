#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "Terrain.h"

//#include "Camera.h"
//#include "md2.h"

using namespace glm;

/**
* @brief Enumerator for asset types
*
* This enumerator is used to assign different types of assets to
* a corresponding value. Used in creation of assets.
*
* @note Currently not entirely implemented.
*
* @author Michael Bell
*/
typedef enum
{
	ASS_NULL = 0,
	ASS_OBJECT = 1,
	ASS_NPC = 2,
	ASS_PLAYER = 3,
	ASS_STRUCTURE = 4
}ASS_TYPE;

/**
* @class IGameAsset
* @brief Interface class for game assets
*
* This class is an interface class for other assets to inherit from.
* Contains various helper functions that are to be overridden in the child
* classes.
*
* @author Michael Bell
*
*/

class IGameAsset
{
public:
	/**
	* @brief Default constructor
	*
	* Empty default constructor.
	*
	* @return null
	*/
	IGameAsset() { }

	/**
	* @brief Default constructor
	*
	* Empty destructor.
	*
	* @return null
	*/
	~IGameAsset() { }

	/**
	* @brief Load object from file path
	*
	* Virtual function taking a file path as a string parameter to load a file.
	*
	* @param std::string filePath
	* @return void
	*/
	virtual void LoadFromFilePath(const char * modelFileName, const char * modelSkinFileName) = 0;

	/**
	* @brief Destroys the asset
	*
	* Virtual function to destroy the asset data for memory management.
	*
	* @return const void
	*/
	virtual const void Destroy() = 0;

	/**
	* @brief Gets the asset file path
	*
	* Virtual function to return a file path.
	*
	* @return const std::string
	*/
	virtual const std::string& GetFilePath() const = 0;
	/**
	* @brief Sets the asset animation
	*
	* Virtual function to set the animation
	*
	* @param std::int  animId the id of the animation
	* @return void
	*/
	virtual void SetAnimation(int animId) = 0;
	/**
	* @brief Sets the asset file path
	*
	* Virtual function to set a file path.
	*
	* @param const std::string& filePath
	* @return void
	*/
	virtual void SetFilePath(const std::string& filePath) = 0;

	/**
	* @brief Gets the asset type
	*
	* Virtual function to return the asset type.
	*
	* @return ASS_TYPE
	*/
	virtual const ASS_TYPE GetOBJType() const { return m_assetType; }

	/**
	* @brief Gets the asset name
	*
	* Virtual function to return the objects name which is its corresponding
	* key to reference it.
	*
	* @return const std::string const
	*/
	virtual const std::string GetAssetName() const { return m_assetName; }

	/**
	* @brief Sets the camera object
	*
	* Sets the camera object to the world camera object to retrieve the view and projection
	* matrices.
	*
	* @param Camera* camera
	* @return void
	*/
	//virtual void SetCamera(CCamera* camera) = 0;

	/**
	* @brief Sets the asset position
	*
	* Virtual function to set the position of the asset.
	*
	* @param glm::vec3 position
	* @return void
	*/
	virtual void SetPosition(vec3 position) = 0;
	/**
	* @brief Sets the asset position
	*
	* Virtual function to set the position of the asset.
	*
	* @param float x the x value
	* @param float z the z value
	* @param Terrain t , the terrain to get the new height from
	* @return void
	*/
	virtual void SetPosition(float x, float z, Terrain& t) = 0;

	/**
	* @brief Sets the asset scale
	*
	* Virtual function to set the scale of the asset.
	*
	* @param glm::vec3 scale
	* @return void
	*/
	virtual void SetScale(float scale) = 0;

	/**
	* @brief Sets the asset rotation
	*
	* Virtual function to set the rotation of the asset.
	*
	* @param glm::vec3 rotation
	* @return void
	*/
	virtual void SetRotation(vec3 rotation) = 0;

	/**
	* @brief Gets the asset position
	*
	* Virtual function to get the position of the asset.
	*
	* @return const glm::vec3
	*/
	//virtual vec3 GetPosition() = 0;

	/**
	* @brief Gets the asset rotation
	*
	* Virtual function to get the position of the asset.
	*
	* @return const glm::vec3
	*/
	//virtual vec3 GetRotation() = 0;

	/**
	* @brief Gets the assets model object
	*
	* Virtual function to get the assets model.
	*
	* @return Model*
	*/
	//virtual MD2Model* GetModel() = 0;

	/**
	* @brief Adds a texture to the model
	*
	* Virtual function to add a texture to the assets mdoel. This takes a
	* texture Id and relative texture file path and adds it.
	*
	* @param GLuint textureId
	* @param std::string textureFilePath
	* @return void
	*/
	//virtual void AddTexutre(GLuint textureId, std::string textureFilePath) = 0;

	/**
	* @brief updates the asset using its update function
	*
	* Virtual function to updates the asset.
	* @param float deltaTime the elapsed time
	* @param Terrain t the terrain to be used for the update
	* @return const void
	*/
	virtual void Update(float deltaTime, Terrain& t) = 0;
	/**
	* @brief draws the asset 
	*
	* Virtual function to draw the asset.
	* @param float time the time to use for draw 
	* @return void
	*/
	virtual void Draw(float time) = 0;



protected:
	/// Defines the nature of the asset
	ASS_TYPE m_assetType;
	/// Used as the key to access a specific asset
	std::string m_assetName;
};