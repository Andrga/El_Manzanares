// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

class StopOnBorders: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::STOPONBORDER)

	StopOnBorders();
	virtual ~StopOnBorders();
	void initComponent() override;
	void update() override;
private:
	Transform *tr_;
};

