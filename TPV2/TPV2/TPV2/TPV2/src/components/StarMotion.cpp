// This file is part of the course TPV2@UCM - Samir Genaim

#include "StarMotion.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


StarMotion::StarMotion() :
		tr_(), lastUpdate_() {
}

StarMotion::~StarMotion() {
}

void StarMotion::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);

	lastUpdate_ = sdlutils().currRealTime();
}

void StarMotion::update() {

	// update every 50ms
	if (lastUpdate_ + 50 > sdlutils().currRealTime())
		return;

	lastUpdate_ = sdlutils().currRealTime();

	tr_->setWidth(tr_->getWidth() * 0.95f);
	tr_->setHeight(tr_->getHeight() * 0.95f);

	if (tr_->getWidth() < 5 || tr_->getHeight() < 5) {
		mngr_->setAlive(ent_, false);
		auto ginfo = mngr_->getHandler(ecs::hdlr::GAMEINFO);
		mngr_->getComponent<GameCtrl>(ginfo)->onStarDeath();
	} else {
		tr_->setRot(tr_->getRot() + 5.0f);
	}
}
