#pragma once
#include "../ecs/ecs.h"

class BlackHoleFacade
{
public:
	BlackHoleFacade(){}
	virtual ~BlackHoleFacade(){}
	virtual void create_blackholes(int n) = 0;
	virtual void remove_all_blackholes() = 0;
};

