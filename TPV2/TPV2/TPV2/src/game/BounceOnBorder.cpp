// This file is part of the course TPV2@UCM - Samir Genaim

#include "BounceOnBorder.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

BounceOnBorder::BounceOnBorder() {
}

BounceOnBorder::~BounceOnBorder() {
}

void BounceOnBorder::update(Container *o) {

	auto &pos = o->getPos();
	auto &vel = o->getVel();
	auto height_ = o->getHeight();

	// bounce on top/bottom borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (pos.getY() + height_ > sdlutils().height()) {
		pos.setY(sdlutils().height() - height_);
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}

}
