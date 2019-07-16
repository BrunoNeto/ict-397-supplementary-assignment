#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include "GameState.h"
#include "GameFont.h"
#include "PlayState.h"

//	@brief	Specialization of the CGameState class for the menu state.
//			This displays a menu in which the player can start a new game, continue an 
//			existing game, or exit the game.
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0
class CMenuState : public CGameState
{
public:
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~CMenuState();

	/**
	*	@brief Handler for key pressed
	*   @see
	*	@param WPARAM key
	*	@return
	*	@pre
	*	@post
	*/
	void OnKeyDown(WPARAM wKey);
	/**
	*	@brief Draw function for menu state
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	void Draw();
	/**
	*	@brief Initialization for the menu state, checks if game is active. 
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	void EnterState();

	/**
	*	@brief Returns the current state instance
	*   @see
	*	@param StateManager
	*	@return MenuState
	*	@pre
	*	@post
	*/
	static CMenuState* GetInstance(CStateManager* pManager);

protected:
	CMenuState(CStateManager* pManager);

private:
	void SelectionUp(); // Moved up the menu
	void SelectionDown(); // Moved down the menu
	void SelectionChosen(); // Selected an item on the menu

	CGameFont* m_pFont; // Game font
	int m_iCurrentSelection; // Index of the current selected menu item

	CPlayState* m_pCurrentGame; // A pointer to the current active game (if any).

	// The background and title images
	//TImagePtr m_pBackgroundImg;
	//TImagePtr m_pTitleImg;
	//Image* m_pBackgroundImg;
	//Image* m_pTitleImg;

	// The images of the menu items (normal and
	// selected).
	//TImagePtr m_pItemBckgndNormal;
	//TImagePtr m_pItemBckgndSelected;
	//Image* m_pItemBckgndNormal;
	//Image* m_pItemBckgndSelected;

	// The text controls of the different entries.
	CTextControl* m_pNewGameText;
	CTextControl* m_pResumeGameText;
	//CTextControl* m_pScoresText;
	CTextControl* m_pExitText;
};

#endif