#include "NPCStates.h"
#include "npc.h"
#include "Ctime.h"
const float PI = 3.1415926535f;
void Wander::Enter(npc* dude)
{
	//do nothing
}
float degToRad3(float value)
{
	float rad = value * 0.0175;
	return rad;
}
void Wander::Execute(npc* dude)
{	
	
	CTimer::GetInstance()->Initialize();
	
	if (!directionGiven) 
	{
		CTimer::GetInstance()->Update();
		float time = CTimer::GetInstance()->GetTimeMSec();
		/*Having the line below results in an strange glitch, that could prove to be useful.*/
		srand(time); //randomizes the seed
		val = rand()%190+(-180) ;
		
		dude->SetRotationAngle(val);
		//set velocity to new direction
		
		directionGiven = true;
		
	}
	
	
}

void Wander::Exit(npc* dude)
{
	//do nothing
	directionGiven = false;
}
