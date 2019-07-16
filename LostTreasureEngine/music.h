#pragma once

#include <SDL_mixer.h>
#include <iostream>
//	@brief music class for our background music
//	@author Bruno Neto
//	version 1.0
class Music
{
public:
	/**
	*	@brief Music default constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post initialises sdl mixer
	*/
	Music();
	/**
	*	@brief Music default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post closes sdl mixer interface
	*/
	~Music();
	/**
	*	@brief Music load function loads a wav file into the music object
	*   @see
	*	@param filename the filename-filepath of the wav file
	*	@return void
	*	@pre the filename must point to a valid wav file
	*	@post
	*/
	void load(const char* filename);
	/**
	*	@brief music play function for playing loaded wav
	*   @see
	*	@param
	*	@return void
	*	@pre must have loaded wav file first
	*	@post loops until the music object destroyed
	*/
	void play();//loops until the music object destroyed
	
private:
	
	
	Mix_Chunk *music;
	
};

