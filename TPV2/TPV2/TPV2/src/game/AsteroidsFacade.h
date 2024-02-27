// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class AsteroidsFacade {
public:
	AsteroidsFacade() {
	}
	virtual ~AsteroidsFacade() {
	}
	virtual void create_asteroids(int n) = 0;
	virtual void remove_all_asteroids() = 0;
	virtual void split_astroid(entity_t a) = 0;
};

