#include "image.h"
class textureGenerator
{
private:
	image* tex[4]; //textures 0-3, 4 in total
	unsigned char* newTex;
	int newTexWidth;
	int newTexHeight;
	int newTexBPP; // bytes per pixel
	int numTextures;
public:
	textureGenerator();
	~textureGenerator();
	bool addTexture(char* filename);
	int getNumTextures();
	void LoadTexture(string filename);
	bool isLoaded(int index);
	RGB<unsigned char> getColor(int texNum, int x, int y);
	void setColor(int x, int y, RGB<unsigned char> color);
	unsigned char* getTex() { return newTex; }
	bool setupNewTexture(int width, int height);
	float getRange();
	float getTextureMax(int texNum);
	unsigned int getTexWidth(int texNo);
	unsigned int getTexHeight(int texNo);
};

