#pragma once
#include "../ecs/Component.h"
class Transform;

class RotateComponent : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::ROTATE)

	RotateComponent();
	RotateComponent(float);
	void initComponent() override;
	void update() override;

private:
	float angle_;
	Transform* transform_;
};
