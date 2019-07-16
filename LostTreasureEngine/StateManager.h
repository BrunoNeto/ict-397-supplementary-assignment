#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "GameState.h"

//	@brief	Manages the different states of the game.
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0
class CStateManager
{
public:
	/**
	*	@brief Default Constructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	CStateManager();
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	~CStateManager();

	/**
	*	@brief Switches to another active state
	*   @see
	*	@param State to change to
	*	@return void
	*	@pre
	*	@post
	*/
	void ChangeState(CGameState* pNewState)
	{
		if (m_pActiveState)
			m_pActiveState->LeaveState();
		m_pActiveState = pNewState;
		m_pActiveState->EnterState();
	}

	/**
	*	@brief Returns to the current active state
	*   @see
	*	@param
	*	@return Gamestate
	*	@pre
	*	@post
	*/
	CGameState* GetActiveState() { return m_pActiveState; }

	/**
	*	@brief 'Events' function, they are simply redirected to the active state.
	*   @see
	*	@param WPARAM Key pressed
	*	@return void
	*	@pre
	*	@post
	*/
	void OnKeyDown(WPARAM wKey);
	/**
	*	@brief 'Events' function, they are simply redirected to the active state.
	*   @see
	*	@param WPARAM Key pressed
	*	@return void
	*	@pre
	*	@post
	*/
	void OnKeyUp(WPARAM wKey);
	/**
	*	@brief 'Events' function, they are simply redirected to the active state.
	*   @see
	*	@param WPARAM Key pressed
	*	@return void
	*	@pre
	*	@post
	*/
	void OnChar(WPARAM wChar);
	/**
	*	@brief 'Events' function, they are simply redirected to the active state.
	*   @see
	*	@param Current Time
	*	@return void
	*	@pre
	*	@post
	*/
	void Update(DWORD dwCurrentTime);
	/**
	*	@brief 'Events' function, they are simply redirected to the active state.
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void Draw();

private:
	CGameState* m_pActiveState; // Active State of the game (Menu, Play)
};

#endif