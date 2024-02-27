// This file is part of the course TPV2@UCM - Samir Genaim

#include "DeAcceleration.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "Transform.h"

DeAcceleration::DeAcceleration() :
		DeAcceleration(0.995f, 0.05f) {
}

DeAcceleration::DeAcceleration(float factor, float limit) :
		tr_(nullptr), dfactor_(factor), limit_(limit) {
}

DeAcceleration::~DeAcceleration() {
}

void DeAcceleration::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DeAcceleration::update() {
	auto &vel = tr_->getVel();
	vel = vel * dfactor_;
	if (vel.magnitude() < limit_)
		vel.set(0.0f, 0.0f);

}
