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
#include "music.h"
#include "SoundEffect.h"
#include "Ctime.h"
#include "npc.h"
#include "md2.h"
using namespace std;


int w = 800;
int h = 600;
int oldx = w / 2;
int oldy = h / 2;
CCamera* cam;
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
float current;
double old=0;
// initialize timer singleton
CTimer *CTimer::m_singleton = 0;
SoundEffect soundEffectTest;
bool bAnimated = true;
float start = 0.0;
float curt;
float last;
float elapsed;
npc	mynpc;



#define MAX_TEXTURES 100								// The maximum amount of textures to load
// This holds the texture info by an ID
UINT g_Texture[MAX_TEXTURES] = { 0 };
#define DETAIL_ID		6
#define BACK_ID		11		// The texture ID for the back side of the cube
#define FRONT_ID	12		// The texture ID for the front side of the cube
#define BOTTOM_ID	13		// The texture ID for the bottom side of the cube
#define TOP_ID		14		// The texture ID for the top side of the cube
#define LEFT_ID		15		// The texture ID for the left side of the cube
#define RIGHT_ID	16		// The texture ID for the right side of the cube

void Idle() 
{
	CTimer::GetInstance()->Update();
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	curt = timesec;
	elapsed = curt - last;

	last = curt;
	mynpc.Update( bAnimated ? timesec : 0.0, gameWorld);
	glutPostRedisplay();
	
}

///////////////////////////////// DRAW SKY BOX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This draws a sky box centered around X Y Z with a width, height and length
/////
///////////////////////////////// DRAW SKY BOX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void DrawSkyBox(float x, float y, float z, float width, float height, float length)
{
	// Turn on texture mapping if it's not already
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, g_Texture[BACK_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// This centers the sky box around (x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the BACK Side
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	// Bind the FRONT texture of the sky map to the FRONT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[FRONT_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the FRONT Side
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Bind the BOTTOM texture of the sky map to the BOTTOM side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[BOTTOM_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the BOTTOM Side
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();

	// Bind the TOP texture of the sky map to the TOP side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[TOP_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the TOP Side
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);

	glEnd();

	// Bind the LEFT texture of the sky map to the LEFT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[LEFT_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the LEFT Side
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	// Bind the RIGHT texture of the sky map to the RIGHT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[RIGHT_ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

	// Assign the texture coordinates and vertices for the RIGHT Side
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();
}

///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This creates a texture in OpenGL that we can texture map
/////
///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool CreateTexture(GLuint &textureID, const char * szFileName)                          // Creates Texture From A Bitmap File
{
	HBITMAP hBMP;                                                                 // Handle Of The Bitmap
	BITMAP  bitmap;																  // Bitmap Structure

	glGenTextures(1, &textureID);                                                 // Create The Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (!hBMP)                                                                    // Does The Bitmap Exist?
		return FALSE;                                                           // If Not Return False

	GetObject(hBMP, sizeof(bitmap), &bitmap);                                     // Get The Object
																				  // hBMP:        Handle To Graphics Object
																				  // sizeof(bitmap): Size Of Buffer For Object Information
																				  // &bitmap:        Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);                                        // Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, textureID);                                      // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);			  // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			  // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.bmWidth, bitmap.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap.bmBits);
	// MUST NOT BE INDEX BMP, BUT RGB
	DeleteObject(hBMP);                                                           // Delete The Object

	return TRUE;                                                                  // Loading Was Successful
}


void render()
{
	
	//CTimer::GetInstance()->Update();
	//float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	//curt = timesec;
	//elapsed = curt - last;
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	//last = curt;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The View
	glMatrixMode(GL_PROJECTION);		//select the projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
		
	
	cam->Animate(bAnimated ? elapsed : 0.0, gameWorld);//send in arbitrary value for delta time this value calc based on 60 refresh per second and the world so that camera can get the appropriate height
	
	mynpc.Draw(bAnimated ? timesec : 0.0);
	DrawSkyBox(500, 500, 250, 1200, 1000, 1200);
	gameWorld.Draw();
	
	glFlush();
	
	
	
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
	cam->yaw -= deltaX * mouseSensitivity;
	cam->pitch += deltaY * mouseSensitivity;
	oldx = x;
	oldy = y;
	glutPostRedisplay();
	
	
}
vec3 newNpcVel;
void kb(unsigned char kbq, int x, int y)
{
	switch (kbq)
	{
	case 'i':
	case 'I': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 'k':
	case 'K': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case GLUT_ACTIVE_SHIFT:
		cam->velocity = vec3(0, 0, 15);
	case 'w':
		cam->velocity += vec3(0, 0, 2.5);
		
		 break;
	case 's':
		cam->velocity += vec3(0, 0, -2.5);	

		break;
	case 'a':
		cam->velocity += vec3(-2.5, 0, 0);
		
		break;
	case 'd':
		cam->velocity += vec3(2.5, 0, 0);
		
		break;
	case 'm':
	case 'M':
		soundEffectTest.play();
		break;
	case 27:
		exit(0);
		break;
	}
	
}

void  myinit(void)
{
	mynpc.SetModel("models/hueteotl/tris.md2", "models/hueteotl/hueteotl.bmp");
	mynpc.SetAnimation(RUN);
	//mynpc.ScaleNPC(0.25);
	mynpc.SetPosition({ (gameWorld.getWorldSizeX() / 2),300,(gameWorld.getWorldSizeZ() -100) });
	soundEffectTest.load("sample.wav");//load in a random sound effect for testing
	CTimer::GetInstance()->Initialize();
	glClearColor(.75, .75, 1, 1);
	glDisable(GL_TEXTURE_2D);								//disable two dimensional texture mapping
	glDisable(GL_LIGHTING);								//disable lighting
	glDisable(GL_BLEND);									//disable blending
	glEnable(GL_DEPTH_TEST);								//Enable depth testing
	glShadeModel(GL_SMOOTH);								//enable smooth shading
	glClearDepth(1.0);									//depth buffer setup
	glDepthFunc(GL_LEQUAL);								//set the type of depth test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	//the nicest perspective look


	//	Skybox
	CreateTexture(g_Texture[BACK_ID], "Textures\\Back.bmp");		// Load the Sky box Back texture
	CreateTexture(g_Texture[FRONT_ID], "Textures\\Front.bmp");	// Load the Sky box Front texture
	CreateTexture(g_Texture[BOTTOM_ID], "Textures\\Bottom.bmp");	// Load the Sky box Bottom texture
	CreateTexture(g_Texture[TOP_ID], "Textures\\Top.bmp");		// Load the Sky box Top texture
	CreateTexture(g_Texture[LEFT_ID], "Textures\\Left.bmp");		// Load the Sky box Left texture
	CreateTexture(g_Texture[RIGHT_ID], "Textures\\Right.bmp");	// Load the Sky box Right texture


	
	cam->MoveToNow((gameWorld.getWorldSizeX() / 2), float((gameWorld.getHeight((gameWorld.getWorldSizeX() / 2), (gameWorld.getWorldSizeZ() - 20)))+60.0f), (gameWorld.getWorldSizeZ() - 20));
	cam->yaw = 0;
	cam->pitch = -75;
	//glutSetCursor(GLUT_CURSOR_NONE);
	gameWorld.loadWorldTexture();
}

int main(int argc, char** argv) {
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
	Music bgmTest;
	bgmTest.load("supervanz__duskwalkin-loop.wav");
	
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
	bgmTest.play();//music will continually play in a loop for the duration of main(or engine once we get to that point) new tracks can be loaded into the bgm and just call play to chang to the new track
	myinit();
	
	//gluLookAt(100, 300, 700, 0, 50, 0, 0, 1, 0); overall view of terrain
	// Bind the  functions (above) to respond when necessary
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(kb);
	
	glutPassiveMotionFunc(Mouse);
	
	glutDisplayFunc(render);
	glutIdleFunc(Idle);
	glutMainLoop();



	return 0;
}

