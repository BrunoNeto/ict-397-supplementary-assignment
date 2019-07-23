#pragma once

class npc;

template <class entity_type>
class state
{
public:
	/** @~state
	*	@brief: Virtual deconstructor for the State class
	*/
	virtual ~state() {}

	/** @Enter
	*	@brief: Virtual function call for the State class Enter
	*/
	virtual void Enter(entity_type*) = 0;

	/** @Exectue
	*	@brief: Virtual function call for the State class Exectue
	*/
	virtual void Execute(entity_type*) = 0;

	/** @Exit
	*	@brief: Virtual function call for the State class Exit
	*/
	virtual void Exit(entity_type*) = 0;
};

