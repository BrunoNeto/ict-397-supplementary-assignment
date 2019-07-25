#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "md2.h"
#include "Object.h"

using namespace glm;

/**
* @class Player
* @brief Player class data and functionality
*
* The player class represents any character in the game that you can control.
* It requires its own special class because it may contain attributes that other assets
* or objects may not such as health or statistics.
*
* @author Michael Bell
*
*/
class Player
{
public:
	MD2Model* m_playerModel;
	Object* pickedUpItem;

	/**
	* @brief Constructor
	*
	* This constructor takes the a string as the key to reference the player and sets it to the
	* name member variable. 
	*
	* @return null
	*/
	Player(std::string assetName);

	/**
	* @brief Destructor
	*
	* This the empty default destructor.
	*
	* @return null
	*/
	~Player() { }

	/**
	* @brief Load object from file path
	*
	* This function takes a file path as a string parameter to load a file.
	*
	* @param std::string filePath
	* @return void
	*/
	void LoadFromFilePath(const char* filePath);

	/**
	* @brief Destroys the player object
	*
	* This function deallocates any memory that the player class has used. Used
	* for memory management.
	*
	* @return const void
	*/
	const void Destroy();

	/**
	* @brief Gets the file path of the player
	*
	* Returns the file path that the players data was read in from as a string.
	*
	* @return std::string&
	*/
	std::string& GetFilePath() { return m_filePath; }

	/**
	* @brief Sets the file path of the player
	*
	* Sets the file path to which the data was read in from to the string parameter
	* parsed in.
	*
	* @param const std::string& filePath
	* @return void
	*/
	void SetFilePath(const std::string& filePath) { m_filePath = filePath; }

	/**
	* @brief Sets the object that the player has picked up
	*
	* When a player interacts with an object they can pick it up
	* and hold it on the player.
	* 
	* @return void
	*/
	void setPickedUpItem(Object* newObject);

	/**
	* @brief Gets the model of the player
	*
	* Returns a pointer to the model of the player.
	*
	* @return Model*
	*/
	MD2Model* GetModel() { return m_playerModel; }

protected:
	std::string m_filePath;
	std::string m_name;
};