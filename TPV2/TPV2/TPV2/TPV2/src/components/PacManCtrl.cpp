// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManCtrl.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "StarMotion.h"
#include "Transform.h"

PacManCtrl::PacManCtrl() :
		tr_(nullptr) {
}

PacManCtrl::~PacManCtrl() {
}

void PacManCtrl::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void PacManCtrl::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		auto &vel_ = tr_->getVel();
		auto rot = tr_->getRot();

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			tr_->setRot(rot + 5.0f);

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			vel_ = vel_.rotate(5.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			tr_->setRot(rot - 5.0f);

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			vel_ = vel_.rotate(-5.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			// add 1.0f to the speed (respecting the limit 3.0f). Recall
			// that speed is the length of the velocity vector
			float speed = std::min(3.0f, vel_.magnitude() + 1.0f);

			// change the length of velocity vecto to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			vel_ = Vector2D(0, -speed).rotate(rot);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			// subtract 1.0f to the speed (respecting the limit 0.0f). Recall
			// that speed is the length of the velocity vector
			float speed = std::max(0.0f, vel_.magnitude() - 1.0f);

			// change the length of velocity vector to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			vel_ = Vector2D(0, -speed).rotate(rot);
		}
	}
}
