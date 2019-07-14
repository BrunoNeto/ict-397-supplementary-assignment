//main for testing terrain load on execution will load a procedurally generated terrain and display it 
//then key press of r will make the terrain switch to data loaded from raw file and apply texture 
//or t will switch to a newly generated terrain that is textured
//w will activate wireframe mode and s will activate standard view
#include "Terrain.h"
#include "camera.h"
#include "World.h"
#include <iostream>
#include<string>
#include <lua.hpp>
using namespace std;


int w = 800;
int h = 600;
int oldx = w / 2;
int oldy = h / 2;
CCamera cam;
World gameWorld;
float MovementSpeed = 2.0f;
float playerHeight = 5;
const float piover180 = 0.0174532925f;
float heading;
int xpos = gameWorld.getWorldSize() / 2;
int zpos = gameWorld.getWorldSize();
float ypos = (float)gameWorld.getWorldXZHeight(xpos, zpos) + playerHeight;
float globalx = 0.0;
float globaly = 0.0;
float globalz = 0.0;
float mouseSensitivity = 1.0f;
GLfloat	yrot;				// Y Rotation
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0f;
GLfloat	z = 0.0f;
double delta = 0;
double current;
double old=0;
void render()
{
	
	
	current = glutGet(GLUT_ELAPSED_TIME);
	delta = current-old;
	old = current;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The View
	glMatrixMode(GL_PROJECTION);		//select the projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	cam.Animate(0.01666666666666666666666666666667f);//send in arbitrary value for delta time this value calc based on 60 refresh per second
	gameWorld.Render();
	
	glFlush();
	
}
double getTime(double startT)
{
	double time1, delta;
	time1 = glutGet(GLUT_ELAPSED_TIME);
	delta = time1 - startT;
	return delta;
}
void  myReshape(GLsizei width, GLsizei  height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	w = width;
	h = height;
	glViewport(0, 0, w, height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, w / h, .1f, 4000.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}




void Mouse( int x, int y)
{
	
	int deltaX;
	int deltaY;
	deltaY = oldy - y;
	deltaX = oldx - x;
	cam.yaw -= deltaX * mouseSensitivity;
	cam.pitch += deltaY * mouseSensitivity;
	oldx = x;
	oldy = y;
	glutPostRedisplay();
	
	
}

void kb(unsigned char kbq, int x, int y)
{
	switch (kbq)
	{
	case 'i':
	case 'I': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 'k':
	case 'K': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case GLUT_ACTIVE_SHIFT:
		cam.velocity = vec3(0, 0, 15);
	case 'w':
		cam.velocity += vec3(0, 0, 2.5);
		
		
		 break;
	case 's':
		cam.velocity += vec3(0, 0, -2.5);

		
		
		break;
	
	case 'a':
		cam.velocity += vec3(-2.5, 0, 0);
		
		
		break;
		
	case 'd':
		cam.velocity += vec3(2.5, 0, 0);	
		
		break;
	case 27:
		exit(0);
		break;
	}
	
}


void  myinit(void)
{
	glClearColor(.75, .75, 1, 1);
	glDisable(GL_TEXTURE_2D);								//disable two dimensional texture mapping
	glDisable(GL_LIGHTING);								//disable lighting
	glDisable(GL_BLEND);									//disable blending
	glEnable(GL_DEPTH_TEST);								//Enable depth testing
	glShadeModel(GL_SMOOTH);								//enable smooth shading
	glClearDepth(1.0);									//depth buffer setup
	glDepthFunc(GL_LEQUAL);								//set the type of depth test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	//the nicest perspective look
	
	cam.MoveToNow(gameWorld.getWorldSize() / 2, gameWorld.getWorldXZHeight(gameWorld.getWorldSize() / 2, gameWorld.getWorldSize() - 20) + 1, gameWorld.getWorldSize() - 20);
	cam.yaw = 0;
	cam.pitch = -75;
	//glutSetCursor(GLUT_CURSOR_NONE);
	gameWorld.loadWorldTexture();
}

int main() {
	/* working example of lua to show its plugged in and working
	//create lua state
	lua_State* L = lua_open();
	// load lua libraries
	luaL_openlibs(L);
	// Do stuff with lua code.
	//lab task2
	cout << "Task 2" << endl;
	luaL_dofile(L, "examplescript.lua");
	*/
	char *myargv[1];
	int myargc = 1;
	myargv[0] = _strdup("lab 2");
	// Initialize GLUT
	glutInit(&myargc, myargv);
	glutInitWindowPosition(0, 0);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Create the window 
	glutCreateWindow(_strdup("Terrain lab, GL"));
	myinit();
	
	//gluLookAt(100, 300, 700, 0, 50, 0, 0, 1, 0); overall view of terrain
	// Bind the  functions (above) to respond when necessary
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(kb);
	
	glutPassiveMotionFunc(Mouse);
	
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutMainLoop();



	return 0;
}

