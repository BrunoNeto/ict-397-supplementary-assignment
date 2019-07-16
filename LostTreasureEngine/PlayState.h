#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameState.h"
#include "GameFont.h"
#include "TextControl.h"

//	@brief	This class represents the play state and will handle the main state
//			of the game.
//	@author Michael Bell
//	@date	15 / 07 / 2019
//	version 1.0


class CPlayState : public CGameState
{
public:
	/**
		*	@brief PlayState default constructor
		*   @see
		*	@param
		*	@return
		*	@pre
		*	@post
		*/
	~CPlayState();

	// Implementation of specific events
	/**
		*	@brief Detects the key press 
		*   @see
		*	@param Key that was pressed
		*	@return
		*	@pre
		*	@post
		*/
	void OnKeyDown(WPARAM wKey);
	/**
		*	@brief
		*   @see
		*	@param
		*	@return
		*	@pre
		*	@post
		*/
	void Update(DWORD dwCurrentTime);
	/**
		*	@brief
		*   @see
		*	@param
		*	@param
		*	@return
		*	@pre
		*	@post
		*/
	void Draw();

	void Reset();
	bool IsGameOver() { return m_bGameOver; }

	// Returns the single instance
	static CPlayState* GetInstance(CStateManager* pManager);

protected:
	CPlayState(CStateManager* pManager);

private:
	// The font used to draw text
	CGameFont* m_pFont;

	// The text controls to display the current
	// information.
	//CTextControl* m_pScoreControl;
	//CTextControl* m_pLevelControl;
	//CTextControl* m_pLinesControl;

	// The current score
	ULONG m_ulCurrentScore;

	bool m_bGameOver;
};

#endif 