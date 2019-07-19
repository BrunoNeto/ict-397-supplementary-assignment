#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Terrain.h"
#include "Audio.h"
#include <string>

#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


#include "NPC.h"
#include<ctime>


using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Used for experimenting with a camera
/*
GLdouble Camera[] = { 100, 400, 200, // initial camera location
					  0, 10, 0, // initial look at point
					  0, 1, 0 };  // initial  upvector
*/
float angle = 0.0;
float x = 100.0f, y = 100.0f, z = 400.0f;
float lx = 0.0f, ly = y, lz = -1.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;

int xOrigin = -1;
int RenderMethod = 0;

Terrain T;
Audio A1("Humans.wav");

NPC p;
NPC p2;

//AudioSE A2("zoroark.WAV");

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//T.BruteForceRender();

	/*gluLookAt(Camera[0], Camera[1], Camera[2], // initial camera location
			  Camera[3], Camera[4], Camera[5], // initial look at point
			  Camera[6], Camera[7], Camera[8]);  // initial  upvector*/

	glutSwapBuffers();
}

void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);

	//Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	//Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);


	/*
	*	BRUNO NOTE HERE:
	*
	* Call the NPC update function
	* each time the glutdisplayFunc loops
	*
	*/
	p.update();
	//p2.update();

	//cout << "p1: " << p.GetDir() << "  p2: " << p2.GetDir() << endl;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//============================================
	// RELOCATE CAMERA:

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
	    x + lx, ly, z + lz,
		0.0f, 1.0f, 0.0f);


	// Draw ground
	/*glColor3f(0.9f, 0.9f, 0.9f);
		glBegin(GL_QUADS);
	    glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
		glEnd();*/

	T.BruteForceRender();

	// Draw 36 SnowMen
	/*for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}*/

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	float fraction = 0.1f;

	switch (key)
	{
	case 'w': 
		x += lx * fraction;
		z += lz * fraction;
		break;

	case 'a':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case 's':
		x -= lx * fraction;
		z -= lz * fraction;
		break;

	case 'd':
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	}
}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
		case GLUT_KEY_UP: deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}



void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			deltaAngle = 0.0f;
			xOrigin = -1;
		}
		else // state = GLUT_DOWN
		{
			xOrigin = x;
		}
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


void SwitchRenderMethod()
{
	if (RenderMethod == 1)
	{
		RenderMethod = 0;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		
	}
	else
	{
		RenderMethod =1;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void pressNKey(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'a': deltaAngle = -0.01f; break;
	case 'd': deltaAngle = 0.01f; break;
	case 'w': deltaMove = 0.5f; break;
	case 's': deltaMove = -0.5f; break;
	case 'r':
		y += 0.5f;
		ly += 0.5;
		A1.playBG();
		break;
	case 'f':
		y -= 0.5f;
		ly -= 0.5f;
		break;
	case 'q': ly += 0.1f; break;
	case 'e': ly -= 0.1f; break;
	case 'p':  SwitchRenderMethod();
				break;

	}
}

void releaseNKey(unsigned char key, int x, int y) {

	switch (key) {

	case 'a':
	case 'd': deltaAngle = 0.0f; break;
	case 'w':
	case 's': deltaMove = 0; break;
	}
}


int main()
{

	string FileName = "height128.raw";
	int FileSize = 128; //imageSize in width

	T.loadHeightfield(FileName, FileSize);
	T.setScalingFactor(4, 0.5, 4);
	

	char *myargv[1];
	int myargc = 1;
	myargv[0] = _strdup("Lab 4");
	/*
	//glutInit(&myargc, myargv);
	//glutInitWindowPosition(0, 0);
	//glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//glutCreateWindow(_strdup("TerrainGenerator")); //title of window

	//

	//gluLookAt(Camera[0], Camera[1], Camera[2], // initial camera location
	//	      Camera[3], Camera[4], Camera[5], // initial look at point
	//	      Camera[6], Camera[7], Camera[8]);  // initial  upvector
	//gluLookAt(100, 400, 200, 0, 10, 0, 0, 1, 0);

	//glutDisplayFunc(Display);
	//glutKeyboardFunc(keys);

	//
	//glutMainLoop();

	//return(0);

	// init GLUT and create window
	*/


	/*
	* BRUNO please add the line below, otherwise the AI will always conduct the same EXACT movements.
		It must be added on the start of the program, otherwise strange issues can and probably
		will occur.
	*/
	srand(static_cast<unsigned>(time(0))); //randomizes the seed

	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(pressNKey);
	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardUpFunc(releaseNKey);


	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	gluPerspective(60, 800 / 600, 0.1, 10000);


	/*Initialised Uptop Now*/
	//Audio A1("Humans.wav");
	//AudioSE A2("zoroark.WAV"); //Used for testing Sound Effects only

	//A1.playBG(); //Start BG music

	// enter GLUT event processing cycle
	glutPostRedisplay();
	glutMainLoop();

	return 1;
}
