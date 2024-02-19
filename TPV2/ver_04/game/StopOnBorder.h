// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class StopOnBorder: public PhysicsComponent {
public:
	StopOnBorder();
	virtual ~StopOnBorder();
	void update(Container *o) override;
};

