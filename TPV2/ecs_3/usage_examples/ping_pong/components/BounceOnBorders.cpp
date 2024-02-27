// This file is part of the course TPV2@UCM - Samir Genaim

#include "BounceOnBorders.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

BounceOnBorders::BounceOnBorders() :
		tr_(nullptr) {
}

BounceOnBorders::~BounceOnBorders() {
}

void BounceOnBorders::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void BounceOnBorders::update() {
	auto &pos = tr_->getPos();
	auto &vel = tr_->getVel();

	// check upper/lower borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.setY(-vel.getY());
		// play some sound
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (pos.getY() + tr_->getHeight() > sdlutils().height()) {
		pos.setY(sdlutils().height() - tr_->getHeight());
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}
}
