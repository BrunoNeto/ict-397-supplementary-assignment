#include "TerrainTextureGenerator.h"
#include <iostream>
#include "ImageLoader.h"
using namespace std;
#include <GL/glut.h>
textureGenerator::textureGenerator()
{
	for (int i = 0; i < 3; i++)
		tex[i] = NULL;
	numTextures = 0;
	newTex = NULL;
	newTexWidth = 0;
	newTexHeight = 0;
	newTexBPP = 3; //24 bits
}
textureGenerator::~textureGenerator()
{
	delete newTex;
	for (int i = 0; i < 3; i++)
		delete tex[i];
}

void loadTexFormat(Image* image, GLuint id) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

}
void textureGenerator::LoadTexture(string filename)
{


	Image *image = loadBMP("texture.bmp");

	loadTexFormat(image,numTextures);
	delete image;
	
}
bool textureGenerator::addTexture(char* filename)
{
	if (numTextures < 3)
	{
		numTextures++;
		//loads texture from file – no opengl setup
		if (tex[numTextures - 1] = texMan.loadTextureRaw(filename))
			return true;
	}
	return false;
}
int textureGenerator::getNumTextures()
{
	return numTextures;
}
bool textureGenerator::isLoaded(int index)
{
	if (index<3 && index >-1)
		return (tex[index] != NULL);
	return false;
}
RGB<unsigned char> textureGenerator::getColor(int texNum, int x, int y)
{
	RGB<unsigned char> val = { 0,0,0 };
	if (texNum > 3 || texNum < 0)
		return val;
	return tex[texNum]->getColor(x, y);
}
void textureGenerator::setColor(int x, int y, RGB<unsigned char> color)
{
	if ((x < newTexWidth) && (y < newTexHeight))
	{
		newTex[((y*newTexHeight) + x)*newTexBPP] = color.r;
		newTex[((y*newTexHeight) + x)*newTexBPP + 1] = color.g;
		newTex[((y*newTexHeight) + x)*newTexBPP + 2] = color.b;
	}
}

bool textureGenerator::setupNewTexture(int width, int height)
{
	//to add - ensure power of 2
	newTexHeight = height;
	newTexWidth = width;
	newTex = new unsigned char[newTexHeight*newTexWidth*newTexBPP];
	if (!newTex)
		return false;
	return true;
}
float textureGenerator::getRange()
{
	if (numTextures > 0)
		return 255.0 / (float)numTextures;
	return 0.0;
}
float textureGenerator::getTextureMax(int texNum)
{
	if (texNum > numTextures - 1)
		return 0.0;
	else
		return((255.0 / (float)numTextures)*(texNum + 1));
}
unsigned int textureGenerator::getTexWidth(int texNo)
{
	if (texNo > 0 && texNo < numTextures)
		return tex[texNo]->getWidth();
	return -1;
}
unsigned int textureGenerator::getTexHeight(int texNo)
{
	if (texNo > 0 && texNo < numTextures)
		return tex[texNo]->getHeight();
	return -1;
}
