// This file is part of the course TPV2@UCM - Samir Genaim

#include "StopOnBorders.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

StopOnBorders::StopOnBorders() :
		tr_() {
}

StopOnBorders::~StopOnBorders() {
}

void StopOnBorders::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void StopOnBorders::update() {
	auto &pos = tr_->getPos();
	auto &vel = tr_->getVel();

	// check upper/lower borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.set(0.0f, 0.0f);
	} else if (pos.getY() + tr_->getHeight() > sdlutils().height()) {
		pos.setY(sdlutils().height() - tr_->getHeight());
		vel.set(0.0f, 0.0f);
	}
}
