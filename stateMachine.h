#pragma once
#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include<iostream>
using namespace std;
#include "state.h"

template <class entity_type>
class stateMachine
{
private:
	entity_type* owner; //Owner of the StateMachine - usually an NPC
	state<NPC> *previousState; //Previous state of the StateMachine, not particularly needed
	state<NPC> *currentState; //Current state of the StateMachine, the State it currently processes
	state<NPC> *globalState; //Global state of the StateMachine, not particularly needed

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
#endif
