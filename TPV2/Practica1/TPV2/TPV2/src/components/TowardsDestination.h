// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;

class TowardsDestination: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::TOWARDSDESTINATION)

	TowardsDestination();
	virtual ~TowardsDestination();
	void initComponent() override;
	void update() override;
private:
	void chage_dest();
	Vector2D dest_;
	Transform *tr_;
	float limit_;
};

