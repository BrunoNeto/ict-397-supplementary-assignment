//main for testing terrain load on execution will load a procedurally generated terrain and display it 
//then key press of r will make the terrain switch to data loaded from raw file and apply texture 
//or t will switch to a newly generated terrain that is textured
//w will activate wireframe mode and s will activate standard view

#include "PlayState.h"
#include "StateManager.h"
#include "MenuState.h"

#include "camera.h"
#include "World.h"
#include <iostream>
#include<string>
#include <lua.hpp>
#include "music.h"
#include "SoundEffect.h"
#include "Terrain.h"
#include <sstream>

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
double old = 0;

SoundEffect soundEffectTest;
Music bgmTest;

using namespace std;

CPlayState::CPlayState(CStateManager* pManager)
	: CGameState(pManager), 
	m_pFont(NULL),
	m_ulCurrentScore(0),
	m_bGameOver(false)
{
	AddFontResource("01 Digitall.ttf");
	m_pFont = new CGameFont;
	m_pFont->CreateFont("01 Digitall", 20, FW_NORMAL);

	// Initialize GLUT
	//glutCreateWindow(_strdup("Terrain lab, GL"));
	//glutInit();
	//glutInitWindowPosition(0, 0);
	// Set the window size
	//glutInitWindowSize(800, 600);
	// Set up some memory buffers for our display
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);


	MyInit();
}

CPlayState::~CPlayState()
{
	if (m_pFont)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
	RemoveFontResource("01 Digitall.ttf");
}

CPlayState* CPlayState::GetInstance(CStateManager* pManager)
{
	static CPlayState Instance(pManager);
	return &Instance;
}

void CPlayState::Reset()
{
	m_ulCurrentScore = 0;
	m_bGameOver = false;
}

void CPlayState::OnKeyDown(WPARAM wKey)
{
	// TODO:
	// Change all game functionality from the main.cpp and factor it into this as that is currently the playstate
	switch (wKey)
	{
	case 'i':
	case 'I': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 'k':
	case 'K': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case GLUT_ACTIVE_SHIFT:
		cam.velocity = vec3(0, 0, 15);
	case VK_UP:
		cam.velocity += vec3(0, 0, 2.5);
		break;
	case VK_DOWN:
		cam.velocity += vec3(0, 0, -2.5);
		break;

	case VK_LEFT:
		cam.velocity += vec3(-2.5, 0, 0);
		break;
	case VK_RIGHT:
		cam.velocity += vec3(2.5, 0, 0);
		break;
	case 'm':
	case 'M':
		soundEffectTest.play();
		break;
	case VK_ESCAPE:
		ChangeState(CMenuState::GetInstance(m_pStateManager));
		break;
	case VK_RETURN:
		if (m_bGameOver)
		{
			// Change state high score, menu or whatever we choose
		}
	}
}

void CPlayState::Update(DWORD dwCurrentTime)
{
	if (!m_bGameOver)
	{
		//Render();
		// Update functions
	}
}

void randomfunc() {
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


	// Create the window 
	glutCreateWindow(_strdup("Terrain lab, GL"));
	//myinit();

	//gluLookAt(100, 300, 700, 0, 50, 0, 0, 1, 0); overall view of terrain
	// Bind the  functions (above) to respond when necessary
	//glutReshapeFunc(myReshape);
	//glutKeyboardFunc(kb);

	

	
	
	
}

void CPlayState::Draw()
{
	if (m_bGameOver)
	{
		// In game over, we draw a semi-transparent black screen on top
		// of the background. Possible with blending
		glColor4f(0.0, 0.0, 0.0, 0.5);
		// Disable 2D texturing because we want to draw a non
		// textured rectangle over the screen.
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 600, 0);
		glVertex3i(800, 600, 0);
		glVertex3i(800, 0, 0);
		glEnd();
		glEnable(GL_TEXTURE_2D);

		m_pFont->DrawText("GAME OVER", 340, 200);
		m_pFont->DrawText("Press Enter to continue", 285, 300);
	}

}


void Render()
{
	current = glutGet(GLUT_ELAPSED_TIME);
	delta = current - old;
	old = current;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The View
	glMatrixMode(GL_PROJECTION);		//select the projection matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam.Animate(0.005f, gameWorld);//send in arbitrary value for delta time this value calc based on 60 refresh per second and the world so that camera can get the appropriate height

	gameWorld.Render();

	glFlush();
}
double GetTime(double startT)
{
	double time1, delta;
	time1 = glutGet(GLUT_ELAPSED_TIME);
	delta = time1 - startT;
	return delta;
}
void  MyReshape(GLsizei width, GLsizei  height)
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


void Mouse(int x, int y)
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

void  CPlayState::MyInit(void)
{
	//glutPassiveMotionFunc(Mouse);
	//glutDisplayFunc(Render);
	//glutIdleFunc(Render);
	//glutMainLoop();
	bgmTest.load("supervanz__duskwalkin-loop.wav");
	bgmTest.play();//music will continually play in a loop for the duration of main(or engine once we get to that point) new tracks can be loaded into the bgm and just call play to chang to the new track
	soundEffectTest.load("sample.wav");//load in a random sound effect for testing
	glClearColor(.75, .75, 1, 1);
	glDisable(GL_TEXTURE_2D);								//disable two dimensional texture mapping
	glDisable(GL_LIGHTING);								//disable lighting
	glDisable(GL_BLEND);									//disable blending
	glEnable(GL_DEPTH_TEST);								//Enable depth testing
	glShadeModel(GL_SMOOTH);								//enable smooth shading
	glClearDepth(1.0);									//depth buffer setup
	glDepthFunc(GL_LEQUAL);								//set the type of depth test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	//the nicest perspective look

	

	cam.MoveToNow((gameWorld.getWorldSizeX() / 2), float((gameWorld.getHeight((gameWorld.getWorldSizeX() / 2), (gameWorld.getWorldSizeZ() - 20))) + 60.0f), (gameWorld.getWorldSizeZ() - 20));
	cam.yaw = 0;
	cam.pitch = -75;
	//glutSetCursor(GLUT_CURSOR_NONE);
	gameWorld.loadWorldTexture();
}
