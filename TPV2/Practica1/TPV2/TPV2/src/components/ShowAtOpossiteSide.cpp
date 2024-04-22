// This file is part of the course TPV2@UCM - Samir Genaim

#include "ShowAtOpossiteSide.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
ShowAtOpossiteSide::ShowAtOpossiteSide() :
		tr_(nullptr) {
}

ShowAtOpossiteSide::~ShowAtOpossiteSide() {
}

void ShowAtOpossiteSide::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ShowAtOpossiteSide::update() {
	auto &pos = tr_->getPos();
	auto h = tr_->getHeight();
	auto w = tr_->getWidth();

	if (pos.getY() + h < 0.0f) {
		pos.setY(sdlutils().height() - 1);
	} else if (pos.getY() > sdlutils().height()) {
		pos.setY(-h + 1);
	}

	if (pos.getX() + w < 0.0f) {
		pos.setX(sdlutils().width() - 1);
	} else if (pos.getX() > sdlutils().width()) {
		pos.setX(-w + 1);
	}

}
