#include "Terrain.h"


Terrain::Terrain() {  }
Terrain::~Terrain() 
{
	delete terrainData;
}
void Terrain::loadTexFormat(Image* image) {
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width, image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
	
}
void Terrain::LoadTexture()
{
	
	
	Image *image = loadBMP("grasstile.bmp");

	loadTexFormat(image);
	delete image;
	textureMapping = true;
}
bool Terrain::unLoadHeightField() 
{
	terrainData = NULL;
	return true;
}
bool Terrain::LoadHeightField(string filename, const int size) {
	//open for binary read
	ifstream infile(filename, ios::binary);
	if (!infile)
	{
		cout << "Cannot open heightmap file " << endl;
		return false;
	}
	//allocate memory
	if (terrainData)
	{
		delete[] terrainData;
	}
	if (size > 0)
	{
		terrainData = new unsigned char[size*size];
	}
	if (terrainData == NULL)
	{
		return false;
	}
	//read in heightfield.
	// get length of file:
	infile.seekg(0, ios::end);
	int length = infile.tellg();

	// read data as a block:
	infile.seekg(0, ios::beg);
	infile.read(reinterpret_cast<char *>(terrainData), length);
	infile.close();
	this->size = size;
	return true;
}
void Terrain::filterPass(float* dataP, int increment, float weight) {
	float yprev = *dataP; // the starting point in the terrain array
	int j = increment; // +1, -1, +size, -size
	float k = weight;
	// loop through either
	// one row from left to right (increment = +1), or
	// one row from right to left (increment = -1), or
	// one column from top to bottom (increment = +size), or
	// one column from bottom to top (increment = -size)
	for (int i = 1; i < size; i++) {
		// yi= k yi-1+ (1-k) xi
		*(dataP + j) = k * yprev + (1 - k)*(*(dataP + j)); //
		yprev = *(dataP + j);
		j += increment;
	}
}
void Terrain::addFilter(float* terrainData, float weight) {
	int i;
	//erode left to right, starting at the beginning of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size*i], 1, weight);
	//erode right to left, starting at the end of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size*i + size - 1], -1, weight);
	//erode top to bottom, starting at the beginning of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[i], size, weight);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size*(size - 1) + i], -size, weight);
}
void Terrain::normaliseTerrain(float* terrainData) {
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = terrainData[0];
	fMax = terrainData[0];
	//find the min/max values of the height terrainData
	for (i = 1; i < size*size; i++) {
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255
	for (i = 0; i < size*size; i++)
		terrainData[i] = ((terrainData[i] - fMin) / fHeight)*255.0f;
}

bool Terrain::genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random)
{
	int x1, x2, z1, z2;
	float* heights = NULL;
	int displacement;
	if (hSize <= 0)
		return false;
	if (random) //create truly random map
		srand(time(NULL));
	// allocate memory for heightfield array
	size = hSize;
	heights = new float[size*size]; //allocate memory
	terrainData = new unsigned char[size*size];
	if (heights == NULL || terrainData == NULL)
	{
		return false;
	}
	// initialise the heightfield array to all zeros
	for (int i = 0; i < size*size; i++)
	{
		heights[i] = 0.0;
	}
	// generate heightfield
	for (int j = 0; j < iterations; j++)
	{
		//calculate reducing displacement value - how much to alter height
		displacement = maxHeight - ((maxHeight - minHeight)*j) / iterations;

		//pick the first point P1(x1, z1) at random from the height map
		x1 = (rand() % size);
		z1 = (rand() % size);
		// pick up the second random point P2(x2, z2) and make sure it is
		// different from the first point
		do {
			x2 = (rand() % size);
			z2 = (rand() % size);
		} while (x2 == x1 && z2 == z1);
		//for each point P(x, z) in the field, calculate the new height values
		for (int z = 0; z < size; z++) {
			for (int x = 0; x < size; x++) {
				// determine which side of the line P1P2 the point P lies in
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
					heights[(z*size) + x] += (float)displacement;
				}
			}
		}
		addFilter(heights, weight);
	}



	// normalise the heightfield
	normaliseTerrain(heights);
	// copy the float heightfield to terrainData (in unsign char)
	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			setHeightAtPoint((unsigned char)heights[(z*size) + x], x, z);
		}
	}
	// dispose of the temporary array heights
	delete[] heights;
	return true;
}
void Terrain::setHeightAtPoint(unsigned char value, int x, int z)
{
	terrainData[z*size + x] = value;
}
void Terrain::setScalingFactor(float xScale, float yScale, float zScale) {
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
}

float Terrain::getScaleX() {
	return scaleX;
}

float Terrain::getScaleY() {
	return scaleY;
}

float Terrain::getScaleZ() {
	return scaleZ;
}

unsigned char Terrain::getHeightColor(int xpos, int zpos) {
	if ((xpos >= 0) && (xpos <= size) && (zpos >= 0) && (zpos <= size))
	{
		return terrainData[zpos*size + xpos];
	}
	else return 1;
}

float Terrain::getHeight(int xpos, int zpos)
{
	
	if (xpos >= 0 && xpos <= size && zpos >= 0 && zpos <= size)
	{
		return ((float)(terrainData[zpos*size + xpos ])*scaleY);
	}
	else {
		xpos = xpos / scaleX;
		zpos = zpos / scaleZ;
		return float(terrainData[zpos*size + xpos]*scaleY);
	}
}
void Terrain::setLightColor(vec3 color) 
{
	lightColor = color;
}
vec3 Terrain::getLightColor() 
{
	return lightColor;
}
unsigned char Terrain::getUnscaledHeight(int xpos, int zpos)
{
	if ((xpos >= 0) && (xpos <= size) && (zpos >= 0) && (zpos <= size))
	{
		return ((float)(terrainData[(zpos*size) + xpos]));
	}
	else return 1;
}
int Terrain::getSize() 
{
	return size;
}
float Terrain::getWorldSizeX()
{
	return float(size*scaleX);
}

float Terrain::getWorldSizeZ()
{
	return float(size*scaleZ);
}
float Terrain::inWorld(float& x, float& z)
{
	if (x < 0)
	{
		x = 0;
		return false;
	}
	else if (x > getWorldSizeX())
	{
		x = getWorldSizeX();
		return false;
	}
	if (z < 0)
	{
		z = 0;
		return false;
	}
	else if (z > getWorldSizeZ())
	{
		z = getWorldSizeZ();
		return false;
	}
	return true;
}

void Terrain::bruteForceRender() {
	vec3 temp;
	temp.r = 255;
	temp.g = 255;
	temp.b = 0;
	setLightColor(temp);
	unsigned char hcolor; //color of the height
	float texLeft, texBottom, texTop; //variables for texture
	//if the texture is loaded then enable texturing and bind our texture
	//textMapping is a new bool instance variable in the terrain class
	
	if (textureMapping) {
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texId);
		//glActiveTexture(texId);
	}
	//loop through the z axis
	glPushMatrix();
	
	for (int z = 0; z < size - 1; z++) {
		//loop through the x axis
		
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < size; x++) {
			//calculate the texture coordinates
			texLeft = (float)x / size;
			texBottom = (float)z / size;
			texTop = (float)(z + 1) / size;


			// color and texture for point (x, z)
			//shade high and low for lighting
			float shadeHigh = (float)getUnscaledHeight(x, z + 1);
			float shadeLow = (float)getUnscaledHeight(x, z);
			
			hcolor = getHeightColor(x, z);
			lightColor = getLightColor();
			//glColor4ub(hcolor, hcolor, hcolor);
			glColor4ub(-shadeLow*lightColor.r, -shadeLow*lightColor.g, -shadeLow*lightColor.b, 255);
			
			glTexCoord2f(texLeft, texBottom);
			glVertex3f((float)x*scaleX, getHeight(x, z), (float)z*scaleZ);
			// color and texture for point (x, z+1)
			hcolor = getHeightColor(x, z + 1);
			lightColor = getLightColor();
			glColor4ub(-shadeHigh*lightColor.r, -shadeHigh*lightColor.g, -shadeHigh*lightColor.b, 255);
			//glColor4ub(hcolor, hcolor, hcolor);
			
			glTexCoord2f(texLeft, texTop);
			glVertex3f((float)x*scaleX, getHeight(x, z + 1), (float)(z + 1)*scaleZ);
		}
		glEnd();
		
	}
	glPopMatrix();
}