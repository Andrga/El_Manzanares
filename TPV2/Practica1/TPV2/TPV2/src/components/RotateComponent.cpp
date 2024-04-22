#include "RotateComponent.h"
#include "Transform.h"
#include "../ecs/Manager.h"

RotateComponent::RotateComponent() :
	RotateComponent(1)
{
}

RotateComponent::RotateComponent(float rot) : angle_(rot)
{
}

void RotateComponent::initComponent() {
	transform_ = mngr_->getComponent<Transform>(ent_);
	assert(transform_ != nullptr);
}

void RotateComponent::update() {
	transform_->setRot(transform_->getRot() + angle_);
}