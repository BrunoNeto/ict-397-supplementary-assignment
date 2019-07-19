#pragma once
#include <Windows.h>
#include <iostream>
#include <stdio.h>
//	@brief lightweight bmp loader that keep all the info in the headers to be used for mapping char textures to md2 models
//	@author Bruno Neto
//	version 1.0
class BMPLoader
{
public:
	unsigned char* textureData;
	int iwidth, iheight;
	/**
	*	@brief constructor method makes a bmploader object which holds the bmp data
	*   @see
	*	@param filename the directory and filename of the bitmap file to be read
	*	@return 
	*	@pre filename should point to a valid 24 bit bitmap file 
	*	@post
	*/
	BMPLoader(const char* filename);
	/**
	*	@brief destructor method deletes pointer objects
	*   @see
	*	@param
	*	@return 
	*	@pre
	*	@post
	*/
	~BMPLoader();

private:
	//var to hold the bitmapfileheader data
	BITMAPFILEHEADER bfh;
	//var to hold the bitmapinfoheader data
	BITMAPINFOHEADER bih;
};

