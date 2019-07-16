#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <Windows.h>

class CStateManager;


//	@brief	Base class for the different states of the game.
//	@author Michael Bell
//	@date	16/07/2019
//	version 1.0
class CGameState
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
	CGameState(CStateManager* pManager);
	/**
	*	@brief Default Destructor
	*   @see
	*	@param
	*	@return
	*	@pre
	*	@post
	*/
	virtual ~CGameState();

	// The different 'events' functions. Child classes can 
	// implement the ones in which they are interested in.
	/**
	*	@brief On key pressed function
	*   @see
	*	@param Key that was pressed
	*	@return void
	*	@pre
	*	@post
	*/
	virtual void OnKeyDown(WPARAM) { }
	/**
	*	@brief On key released function
	*   @see
	*	@param Key that was pressed
	*	@return void
	*	@pre
	*	@post
	*/
	virtual void OnKeyUp(WPARAM) { }
	/**
	*	@brief
	*   @see
	*	@param WPARAM
	*	@return void
	*	@pre
	*	@post
	*/
	virtual void OnChar(WPARAM) { }
	/**
	*	@brief Game update loop
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	virtual void Update(DWORD) { }
	/**
	*	@brief Game draw function
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	virtual void Draw() { }

	// Functions called when the state is entered or left
	// (transition from/to another state).
	virtual void EnterState() { }
	virtual void LeaveState() { }

	// Helper function to switch to a new active state.
	void ChangeState(CGameState* pNewState);

protected:
	

	// The state manager.
	CStateManager* m_pStateManager;
};

#endif