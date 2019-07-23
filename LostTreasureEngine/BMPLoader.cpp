#define _CRT_SECURE_NO_DEPRECATE

#include "BMPLoader.h"


using namespace std;
//loads a bitmap at the location specified in filename
BMPLoader::BMPLoader(const char* filename)
{

	FILE *file = 0;
	file = fopen(filename, "rb");
	if (!file)
	{
		std::cout << "Error : file not found" << std::endl;
	}
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
	if (bfh.bfType != 0x4D42)
	{
		cout << "not a valid bitmap file" << endl;
	}
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
	if (bih.biSizeImage == 0)
	{
		bih.biSizeImage = bih.biHeight*bih.biWidth * 3;
	}
	textureData = new unsigned char[bih.biSizeImage];
	fseek(file, bfh.bfOffBits, SEEK_SET);
	fread(textureData, 1, bih.biSizeImage, file);
	unsigned char temp;
	for (int i = 0; i < bih.biSizeImage; i += 3)
	{
		temp = textureData[i];
		textureData[i] = textureData[i + 2];
		textureData[i + 2] = temp;
	}
	iwidth = bih.biWidth;
	iheight = bih.biHeight;
	fclose(file);

}

//deletes texure data pointer
BMPLoader::~BMPLoader()
{
	delete[]textureData;
}
