#include "NPC.h"
#include "NPCStates.h"

NPC::NPC()
{
	/*
		All of these below are needed to set the State
		DIR is an int held by the NPC, that can be accessed via
		the state, and can be used for your Wander function.
		-	Warning, the AI updates this with each update
	*/
	NPCSM = new stateMachine<NPC>(this);
	NPCSM->setCurrentState(&wander_state::Instance());
	NPCSM->setGlobalState(&wander_state::Instance());
	DIR = 0;
}


NPC::~NPC()
{
	/*
		Please remember to delete the State, else memory leaks will occur
	*/
	delete NPCSM;
}

void NPC::update()
{


	NPCSM->update();	//call the State machines update
	cout << DIR << endl; //just to prove its working
}


/*
	This function is needed so that DIR can be accessed via the State Machine
	otherwise, the code can become really messy
*/
void NPC::SetDir(float value)
{
	DIR = value;
}

/*
Not really needed just figured it may come in useful for later.
\*/
float NPC::GetDir()
{
	return DIR;
}