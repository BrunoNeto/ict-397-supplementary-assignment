#include "NPCStates.h"
#include "npc.h"
//#include<ctime>

void Wander::Enter(npc* dude)
{
	//do nothing
}

void Wander::Execute(npc* dude)
{
	/*Having the line below results in an strange glitch, that could prove to be useful.*/
	//srand(static_cast<unsigned>(time(0))); //randomizes the seed

	float val = rand() % 359;
	dude->SetRotationAngle(val);
}

void Wander::Exit(npc* dude)
{
	//do nothing
}
