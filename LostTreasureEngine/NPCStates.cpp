#include "NPCStates.h"
#include "npc.h"
#include"Ctime.h"
const float PI = 3.1415926535f;
void Wander::Enter(npc* dude)
{
	//do nothing
}

void Wander::Execute(npc* dude)
{	
	CTimer::GetInstance()->Initialize();
	float time = CTimer::GetInstance()->GetTime() ;
	
	if (!directionGiven) 
	{
		
		/*Having the line below results in an strange glitch, that could prove to be useful.*/
		srand(time); //randomizes the seed
		val = (rand() % 360);
		
		dude->SetRotationAngle(val);
		
		directionGiven = true;
		
	}
	
	
}

void Wander::Exit(npc* dude)
{
	//do nothing
	directionGiven = false;
}
