#include "Audio.h"
#include "windows.h"
#include "mmsystem.h"


using namespace std;

Audio::Audio(const char * filename)
{
	buffer = 0;
	ifstream infile(filename, ios::binary);

	if (!infile)
	{
		cout << "File Error:" << filename << " cannot be opened" << endl;
		return;
	}

	infile.seekg(0, ios::end);
	int length = infile.tellg();
	buffer = new char[length];
	infile.seekg(0, ios::beg);
	infile.read(buffer, length);
	infile.close();

	FileOk = true;

	//mciSendString("open \" *.wav\" type mpegvideo alias wav", NULL, 0, NULL);

}

Audio::~Audio()
{
	PlaySound(NULL, 0, 0);
	delete[] buffer;
}

void Audio::playBG()
{
	if (isok())
	{
		PlaySound(buffer, NULL, SND_MEMORY | SND_ASYNC);
	}
}

void Audio::stopBG()
{
	PlaySound(NULL, 0, 0);
}


/**
	Designed to play sound effects without stopping the Background Music
	- STILL IN PROGRESS
*/
void Audio::playSE()
{
	if (isok())
	{
		PlaySound(buffer, NULL, SND_MEMORY | SND_ASYNC);
	}
	
}

bool Audio::isok()
{
	return FileOk;
}