// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

class BounceOnBorders: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::BOUNCEONBORDER)

	BounceOnBorders();
	virtual ~BounceOnBorders();
	void initComponent() override;
	void update() override;
private:
	Transform *tr_;
};

