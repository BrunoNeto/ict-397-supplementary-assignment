#pragma once
#ifndef __NPCSTATES_H
#define	__NPCSTATES_H

#include "singleton.h"
#include "state.h"

class NPC;

class Wander : public state<NPC>
{
public:
	~Wander() {}
	void Enter(NPC* dude);
	void Execute(NPC* dude);
	void Exit(NPC* dude);
};

typedef singleton<Wander> wander_state;

#endif