// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
class Transform;

class Vector2D;

class Follow: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::FOLLOW)

	Follow(Vector2D &to_follow);
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:
	Vector2D &to_follow_;
	Transform *tr_;
};

