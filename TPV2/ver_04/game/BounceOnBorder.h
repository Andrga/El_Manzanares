// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "PhysicsComponent.h"

class BounceOnBorder: public PhysicsComponent {
public:
	BounceOnBorder();
	virtual ~BounceOnBorder();
	void update(Container *o) override;
};

