// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;


class DeAcceleration: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::DEACCELERATION)

	DeAcceleration();
	DeAcceleration(float factor, float limit);
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;
public:
	Transform *tr_;
	float dfactor_;
	float limit_;

};

