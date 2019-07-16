#include "music.h"



Music::Music()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{
		std::cout << "Error: " << Mix_GetError()<<std::endl;
	}
}


Music::~Music()
{
	Mix_CloseAudio();	
}


void Music::load(const char* filename)
{
	
	
	music = Mix_LoadWAV(filename);
	Mix_AllocateChannels(16);
	
}


void Music::play()
{
	Mix_PlayChannel(1, music, -1);
}//loops

