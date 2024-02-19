// This file is part of the course TPV2@UCM - Samir Genaim

#include "StopOnBorder.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

StopOnBorder::StopOnBorder() {
}

StopOnBorder::~StopOnBorder() {
}

void StopOnBorder::update(Container *o) {
	auto &pos_ = o->getPos();
	auto &vel_ = o->getVel();
	auto height_ = o->getHeight();

	if (pos_.getY() < 0) {
		pos_.setY(0);
		vel_.setY(0);
	} else if (pos_.getY() + height_ > sdlutils().height()) {
		pos_.setY(sdlutils().height() - height_);
		vel_.setY(0);
	}
}
