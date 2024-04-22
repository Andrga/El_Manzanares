// This file is part of the course TPV2@UCM - Samir Genaim

#include "FighterCtrl.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
		ihdrl(ih()), tr_(nullptr), thrust_(0.1f), limit_(3.0f) {
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void FighterCtrl::update() {
//	if (ihdrl.keyDownEvent())
	if (ihdrl.isKeyDown(SDL_SCANCODE_RIGHT)) {
		tr_->setRot(tr_->getRot() + 1.0f);
	} else if (ihdrl.isKeyDown(SDL_SCANCODE_LEFT)) {
		tr_->setRot(tr_->getRot() - 1.0f);
	} else if (ihdrl.isKeyDown(SDL_SCANCODE_UP)) {
		auto &vel = tr_->getVel();
		vel = vel + Vector2D(0, -1).rotate(tr_->getRot()) * thrust_;
		if (vel.magnitude() > limit_)
			vel = vel.normalize() * 3.0f;
		sdlutils().soundEffects().at("thrust").play();
	}
}

