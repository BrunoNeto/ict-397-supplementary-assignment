#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <time.h>
#include "ImageLoader.h"

using namespace std; 
using namespace glm;
//	Represents an landscape/terrain asset
//	@brief terrain for representing an landscape/terrain asset
//	@author Bruno Neto
//	version 1.0
class Terrain
{

	public:
		/**
		*	@brief Terrain default constructor 
		*   @see
		*	@param
		*	@return
		*	@pre
		*	@post 
		*/
		Terrain();
		/**
		*	@brief Terrain default deconstructor 
		*   @see
		*	@param 
		*	@return
		*	@pre
		*	@post ps must hold valid pixel data
		*/
		~Terrain();
		/**
		*	@brief method for normalising the height values in a terrain- used for procedural generation
		*   @see
		*	@param terrainData the data of the terrain
		*	@return void
		*	@pre
		*	@post 
		*/
		void normaliseTerrain(float* terrainData);
		/**
		*	@brief method for adding fir filter to a terrain heightmap
		*   @see
		*	@param terrainData the data of the terrain
		*	@param weight the weighting of the fir filter
		*	@return void
		*	@pre
		*	@post 
		*/
		void addFilter(float* terrainData, float weight);
		/**
		*	@brief method for a single pass of the fir filter
		*   @see
		*	@param dataP the actual terrain data
		*	@param increment the number of current increment
		*	@param weight the weighting of the fir filter
		*	@return void
		*	@pre
		*	@post 
		*/
		void filterPass(float* dataP, int increment, float weight);
		/**
		*	@brief method for loading a heightmap from file in raw format
		*   @see
		*	@param size the size of the heightmap
		*	@param filename the filename of the heightmap to load
		*	@return returns true if successful
		*	@pre filename must point to a valid raw file
		*	@post 
		*/
		bool LoadHeightField(string filename, const int size);
		/**
		*	@brief method that unloads assets used by the terrain
		*   @see
		*	@param 
		*	@return returns true if successful
		*	@pre
		*	@post 
		*/
		bool unLoadHeightField();
		/**
		*	@brief method for loading the textures of the world atm only loads terrain
		*   @see
		*	@param 
		*	@return void
		*	@pre
		*	@post
		*/
		void LoadTexture();
		/**
		*	@brief method for generating heightmap procedurally
		*   @see
		*	@param iterations the number of iterations of the fault formation algorithm 
		*	@param hsize size of the heightfield for reference terrain is [size*size] big
		*	@param minheight the minimum height of the heightmap
		*	@param maxheight the maximum height of the heightmap
		*	@param weight the weighting of the fir filter
		*	@param random - wether the generation uses time or not to make completely random seeds use true
		*	@return returns true if succesfull
		*	@pre
		*	@post 
		*/
		bool genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random);
		/**
		*	@brief method for setting the scaling factor of terrain in x,y and z
		*   @see
		*	@param xScale the scale factor in x
		*	@param yScale the scale factor in y
		*	@param zScale the scale factor in z
		*	@return void
		*	@pre
		*	@post 
		*/
		void setScalingFactor(float xScale, float yScale, float zScale);
		/**
		*	@brief method for rendering terrain
		*   @see
		*	@param 
		*	@return void
		*	@pre terrain must have textures loaded before rendering
		*	@post 
		*/
		void bruteForceRender();
		/**
		*	@brief method for getting the scaled height of worlds terrain at particular x,z location
		*   @see
		*	@param x the x value we need hight for
		*	@param z the z value we need hight for
		*	@return returns a float value of the scaled height at location x,z
		*	@pre
		*	@post
		*/
		float getHeight(int xpos, int zpos);
		/**
		*	@brief method for getting the size of the heightmap for ref terrain is [size*size] big
		*   @see
		*	@param
		*	@return the size of the world in integer
		*	@pre
		*	@post
		*/
		int getSize();
		/**
		*	@brief method for getting the color for terrain at particular x,z location
		*   @see
		*	@param x the x value we need get height color for
		*	@param z the z value we need get height color for
		*	@return returns the height colour as a unsigned char
		*	@pre
		*	@post
		*/
		unsigned char getHeightColor(int xpos, int zpos);
		/**
		*	@brief method for setting the height of worlds terrain at particular x,z location
		*   @see
		*	@param height the value to set the height to
		*	@param x the x value we need set height for
		*	@param z the z value we need set height for
		*	@return void
		*	@pre
		*	@post 
		*/
		void setHeightAtPoint(unsigned char height,int x,int z);
		/**
		*	@brief method for loading the format of terrain texture
		*   @see
		*	@param image pointer to an image to be formatted
		*	@return void
		*	@pre
		*	@post 
		*/
		void loadTexFormat(Image* image);
		/**
		*	@brief method for setting the light colour variable
		*   @see
		*	@param color the vec3 colour to set light color to
		*	@return void
		*	@pre
		*	@post 
		*/
		void setLightColor(vec3 color);
		/**
		*	@brief method for getting the light colour variable
		*   @see
		*	@param
		*	@return vec 3 representation of the light color
		*	@pre
		*	@post
		*/
		vec3 getLightColor();
		/**
		*	@brief method for getting the height of worlds terrain at particular x,z location
		*   @see
		*	@param x the x value we need hight for
		*	@param z the z value we need hight for
		*	@return returns a float value of the height at location x,z
		*	@pre
		*	@post
		*/
		unsigned char getUnscaledHeight(int x, int z);
	protected:
		GLuint texId;
		vec3 lightColor;
		unsigned char *terrainData; //data of the heightfield
		float scaleX; //how much we want to scale by
		float scaleY;
		float scaleZ;
		bool textureMapping;
	private:
		int size; //the size of the heightfield along x and z - power of 2


};



