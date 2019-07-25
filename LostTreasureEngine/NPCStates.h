#pragma once

#include "singleton.h"
#include "state.h"

class npc;

class Wander : public state<npc>
{
public:
	~Wander() {}
	void Enter(npc* dude);
	void Execute(npc* dude);
	void Exit(npc* dude);
	bool directionGiven = false;
	float val;
};

typedef singleton<Wander> wander_state;
