// This file is part of the course TPV2@UCM - Samir Genaim

#include "TowardsDestination.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

TowardsDestination::TowardsDestination() :
		dest_(), tr_(nullptr), limit_(10.0f) {
}

TowardsDestination::~TowardsDestination() {

}

void TowardsDestination::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
	chage_dest();
}

void TowardsDestination::update() {
	auto &pos = tr_->getPos();
	if ((pos - dest_).magnitude() < limit_) {
		chage_dest();
	}
}

void TowardsDestination::chage_dest() {
	int x = sdlutils().rand().nextInt(0, sdlutils().width());
	int y = sdlutils().rand().nextInt(0, sdlutils().height());
	dest_ = Vector2D(x, y);

	auto &vel = tr_->getVel();
	auto &pos = tr_->getPos();

	auto v = dest_ - pos;

	vel = vel.rotate(vel.angle(v));
}
