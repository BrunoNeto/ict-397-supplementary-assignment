/*
* 
* @Author - Michael Bell
*/

// Includes
#include "ScriptManager.h"
#include <iostream>

// Default constructor
ScriptManager::ScriptManager() {}

// De-constructor
ScriptManager::~ScriptManager() {}

// Load all scripts
void ScriptManager::LoadAllLuaScripts() {}

bool ScriptManager::LoadNumberOfAssets(int &numberOfStructures, int &numberOfNpcs, int &numberOfObjects)
{
	lua_State* Environment = lua_open();
	if (Environment == NULL)
	{
		// Show error and exit program
		std::cout << "Error Initializing lua.." << std::endl;
		getchar();
		exit(0);
	}

	// Load standard lua library functions
	luaL_openlibs(Environment);

	// Load and run script
	if (luaL_dofile(Environment, "scripts/NumberOfAssets.lua"))
	{
		std::cout << "Error opening file.." << std::endl;
		getchar();
		return false;
	}

	// Read from script
	lua_settop(Environment, 0);
	lua_getglobal(Environment, "NumberOfStructures");
	lua_getglobal(Environment, "NumberOfNpcs");
	lua_getglobal(Environment, "NumberOfObjects");

	numberOfStructures = (int)lua_tonumber(Environment, 1);
	numberOfNpcs = (int)lua_tonumber(Environment, 2);
	numberOfObjects = (int)lua_tonumber(Environment, 3);

	std::cout << "Number of Npcs:" << std::endl;
	std::cout << numberOfNpcs << std::endl;

	// Close environment
	lua_close(Environment);

	// Return true for successful loading and reading
	return true;

}