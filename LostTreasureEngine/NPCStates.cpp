#include "NPCStates.h"
#include "NPC.h"
//#include<ctime>

void Wander::Enter(NPC* dude)
{
	//do nothing
}

void Wander::Execute(NPC* dude)
{
	/*Having the line below results in an strange glitch, that could prove to be useful.*/
	//srand(static_cast<unsigned>(time(0))); //randomizes the seed

	float val = rand() % 359;
	dude->SetDir(val);
}

void Wander::Exit(NPC* dude)
{
	//do nothing
}
