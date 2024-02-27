// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleKBCtrl.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

PaddleKBCtrl::PaddleKBCtrl() :
		tr_(), //
		up_(SDL_SCANCODE_UP), //
		down_(SDL_SCANCODE_DOWN), //
		stop_(SDL_SCANCODE_LEFT), //
		speed_(10.0f) //
{
}

PaddleKBCtrl::~PaddleKBCtrl() {
}

void PaddleKBCtrl::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void PaddleKBCtrl::update() {
	auto &ihdlr = ih();

	auto &vel = tr_->getVel();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(up_)) {
			vel.setY(-speed_);
		} else if (ihdlr.isKeyDown(down_)) {
			vel.setY(speed_);
		} else if (ihdlr.isKeyDown(stop_)) {
			vel.setY(0.0f);
		}
	}
}
