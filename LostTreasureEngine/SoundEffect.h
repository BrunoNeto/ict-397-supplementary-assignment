#pragma once
#include <SDL.h>
#include <iostream>
//	@brief SoundEffect class for games sound effects
//	@author Bruno Neto
//	version 1.0
class SoundEffect
{
public:
	/**
	*	@brief SoundEffect default constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post initialises device to play from
	*/
	SoundEffect();
	/**
	*	@brief SoundEffect default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post closes any open device 
	*/
	~SoundEffect();
	/**
	*	@brief SoundEffect load function loads a wav file into the SoundEffect object
	*   @see
	*	@param filename the filename-filepath of the wav file
	*	@return void
	*	@pre the filename must point to a valid wav file
	*	@post
	*/
	void load(const char* filename);
	/**
	*	@brief SoundEffect play function for playing loaded wav
	*   @see
	*	@param
	*	@return void
	*	@pre must have loaded wav file first
	*	@post plays SoundEffect once
	*/
	void play();//loops until the music object destroyed

private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
};

