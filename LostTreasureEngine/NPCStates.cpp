#include "NPCStates.h"
#include "npc.h"
#include<ctime>
const float PI = 3.1415926535f;
void Wander::Enter(npc* dude)
{
	//do nothing
}

void Wander::Execute(npc* dude)
{	
	
	
	if (!directionGiven) 
	{
		/*Having the line below results in an strange glitch, that could prove to be useful.*/
		srand(static_cast<unsigned>(time(0))); //randomizes the seed
		val = (rand() % 360)*10;
		
		dude->SetRotationAngle(val);
		
		directionGiven = true;
		
	}
	
	
}

void Wander::Exit(npc* dude)
{
	//do nothing
	directionGiven = false;
}
