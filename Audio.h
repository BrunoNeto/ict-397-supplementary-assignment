#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Audio
{
public:
	Audio(const char * filename); //Constructor
	~Audio();	//Deconstructor
	//Designed to play Background Music
	void playBG();	
	//Stop BG music from playing
	void stopBG();
	//Designed to play SoundEffects
	void playSE();		
    //Returns whether the file is readable
	bool isok(); 

private:
	//private char* to hold the memory of the file
	char * buffer;
	//holds whether the file is openable or not
	bool FileOk;

};

