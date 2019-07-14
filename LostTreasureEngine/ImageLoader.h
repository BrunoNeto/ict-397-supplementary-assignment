#pragma once

// Represents an image
//	@brief image class storing pixel data to be read from bitmap files
//	@author Bruno Neto
//	version 1.0
class Image {
public:
	/**
	*	@brief Image default constructor takes a char* of image data and width and height
	*   @see
	*	@param ps the pixel data of the image
	*	@param w the width of the image
	*	@param h the height of the image
	*	@return
	*	@pre ps must hold valid pixel data
	*	@post 
	*/
	Image(char* ps, int w, int h);
	/**
	*	@brief World default deconstructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~Image();
	char* pixels;
	int width;
	int height;
};
//Reads a bitmap image from file
/**
	*	@brief loads a 24bit bmp with the filename given as a parameter and returns a pointer to the image data
	*   @see
	*	@param filename the filename of the 24bit bitmap to load
	*	@return pointer to the image data
	*	@pre
	*	@post
	*/
Image* loadBMP(const char* filename);
 

