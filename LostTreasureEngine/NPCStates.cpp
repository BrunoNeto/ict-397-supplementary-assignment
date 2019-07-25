#include "NPCStates.h"
#include "npc.h"
//#include<ctime>

void Wander::Enter(npc* dude)
{
	//do nothing
}

void Wander::Execute(npc* dude)
<<<<<<< HEAD
{	
	
	
	if (!directionGiven) 
	{
		/*Having the line below results in an strange glitch, that could prove to be useful.*/
		srand(static_cast<unsigned>(time(0))); //randomizes the seed
		val = (rand() % 360)*10;
		
		dude->SetRotationAngle(val);
		
		directionGiven = true;
		
	}
	
	
=======
{
	/*Having the line below results in an strange glitch, that could prove to be useful.*/
	//srand(static_cast<unsigned>(time(0))); //randomizes the seed

	float val = rand() % 359;
	dude->SetRotationAngle(val);
>>>>>>> parent of 4c8f2b9... merged factory into world fixed some wander bug
}

void Wander::Exit(npc* dude)
{
	//do nothing
}
