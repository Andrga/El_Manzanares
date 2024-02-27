// This file is part of the course TPV2@UCM - Samir Genaim

#include "Follow.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

Follow::Follow(Vector2D &to_follow) :
		to_follow_(to_follow), //
		tr_(nullptr) {

}

Follow::~Follow() {
}

void Follow::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Follow::update() {
	auto &pos = tr_->getPos();
	auto &vel = tr_->getVel();

	auto v = to_follow_ - pos;

	vel = vel.rotate(vel.angle(v) > 0 ? 1.0f : -1.0f);
}
