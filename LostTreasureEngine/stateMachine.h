#pragma once

#include<iostream>
using namespace std;
#include "state.h"

template <class entity_type>
class stateMachine
{
private:
	entity_type* owner; //Owner of the StateMachine - usually an NPC
	state<npc> *previousState; //Previous state of the StateMachine, not particularly needed
	state<npc> *currentState; //Current state of the StateMachine, the State it currently processes
	state<npc> *globalState; //Global state of the StateMachine, not particularly needed

	int RandDir = NULL;

public:
	//default constructor
	stateMachine(entity_type* FSMowner)
	{
		owner = FSMowner; //Set the a point to this NPC's owner
		//Set all states to NULL
		previousState = NULL;
		currentState = NULL;
		globalState = NULL;
	}

	//use the following methods to intialise the FSM
	//allows for the setting of different states
	void setPreviousState(state<entity_type>* st) { previousState = st; }
	void setCurrentState(state<entity_type>* st) { currentState = st; }
	void setGlobalState(state<entity_type>* st) { globalState = st; }
	void exitState(npc* owner) {currentState->Exit(owner); }
	void enterState(npc* owner) { currentState->Enter(owner); }
	void executeState(npc* owner) { currentState->Execute(owner); }
	//Called whenever the stateMachine is updated
	void update()const
	{
		/*If statement below not needed*/
		//if (globalState)
		//	globalState->Execute(owner);
		if (currentState)
			currentState->Execute(owner);
	}

	//Getters for each state
	state<entity_type>* getPreviousState() { return previousState; }
	state<entity_type>* getCurrentState() { return currentState; }
	state<entity_type>* getGlobalState() { return globalState; }

	//returns whether the StateMachine is in a particualr state
	bool isInState(const state<entity_type>& st)const
	{
		return typeid(*currentState) == typeid(st);
	}

	//Virtual Deconstructor
	virtual ~stateMachine() {}
};

