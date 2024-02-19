// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Component.h"

class Container;

class PhysicsComponent: public Component {
public:
	PhysicsComponent() {
	}
	virtual ~PhysicsComponent() {
	}

	virtual void update(Container *o) = 0;
};

