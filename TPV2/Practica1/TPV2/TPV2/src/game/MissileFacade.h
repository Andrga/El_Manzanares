#pragma once
#include "../ecs/ecs.h"

class MissileFacade
{
public:
	MissileFacade() {}
	virtual ~MissileFacade() {}
	virtual void create_missiles() = 0;
	virtual void remove_all_missiles() = 0;
};