/**
* @class ScriptManager
* @brief Script manager class that handles the loading of all scripts
* @author Michael Bell
*/

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

// Includes
#include <string>
#include "lua.hpp"
#include <GLM\glm.hpp>

class ScriptManager
{
public:

	/**
	* @brief Singleton instance
	*
	* This function returns a singleton instance of the script manager class so that there is only
	* one instance of a script manager.
	*
	* @return static ScriptManager&
	*/
	static ScriptManager& Instance()
	{
		static ScriptManager instance;

		return instance;
	}

	/**
	* @brief Load all lua scripts
	*
	* Public function that calls a private function for each type of script to load
	*
	* @return void
	*/
	void LoadAllLuaScripts();

	bool LoadNumberOfAssets(int &numberOfStructures, int &numberOfNpcs, int &numberOfObjects);
private:

	/**
	* @brief Default constructor
	*
	* This is the default constructor
	*
	* @return null
	*/
	ScriptManager();

	/**
	* @brief De-constructor
	*
	* This is the de-constructor
	*/
	~ScriptManager();
};

#endif