#include "PlayState.h"
#include "StateManager.h"
#include "MenuState.h"
#include <sstream>

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
	case VK_UP:
		if (!m_bGameOver)
		break;
	case VK_DOWN:
		if (!m_bGameOver)
		break;
	case VK_LEFT:
		if (!m_bGameOver)
		break;
	case VK_RIGHT:
		if (!m_bGameOver)
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
		// Update functions
	}
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