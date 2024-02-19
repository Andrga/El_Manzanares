// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class SimpleMove: public PhysicsComponent {
public:
	SimpleMove();
	virtual ~SimpleMove();
	void update(Container *o) override;
};

