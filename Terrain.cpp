#include "Terrain.h"


using namespace std;

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

bool Terrain::loadHeightfield(string filename, const int size)
{
	//open for binary read
	ifstream infile(filename, ios::binary);

	if (!infile)
	{
		cout << "File cannot be opened: " << endl;
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

	//read in the heightfield
		//get the length of the file
		infile.seekg(0, ios::end);
		int length = infile.tellg();

	//read data as a block
		infile.seekg(0, ios::beg);
		infile.read(reinterpret_cast<char*>(terrainData), length);
		infile.close();
		this->size = size;

		return true;
}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale)
{
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
}

void Terrain::BruteForceRender()
{
	unsigned char hcolour; //colour of the height

	//loop through the z axis
	for (int z = 0; z < (size - 1); z++)
	{
		

		
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < size; x++)
		{
			//create the first point of the triangle strip
			hcolour = getHeightColour(x, z);
			glColor3ub(hcolour, hcolour, hcolour);
			glVertex3f((float)x*scaleX, getHeight(x, z), (float)(z)*scaleZ);

			//create the next point in the triangle strip
			hcolour = getHeightColour(x, z + 1);
			glColor3ub(hcolour, hcolour, hcolour);
			glVertex3f((float)x*scaleX, getHeight(x, z + 1 ), (float)(z + 1)*scaleZ);

		}
		glEnd();
	}
}

float Terrain::getHeight(int xpos, int zpos)
{
	if ((xpos >= 0) && (xpos < zpos))
	{
		return ((float)terrainData[(zpos*size) + xpos]*scaleY);
	}
}

unsigned char Terrain::getHeightColour(int xpos, int zpos)
{
	if ((xpos >= 0) && (xpos < zpos))
	{
		return (terrainData[(zpos*size) + xpos]);
	}
	return 1;
}