// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "StarsSystem.h"
GameCtrlSystem::GameCtrlSystem() :
		score_() {
	// TODO Auto-generated constructor stub

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {

			Message m;
			m.id = _m_CREATE_STARS;
			m.create_stars_data.n = 5;
			mngr_->send(m);
		}
	}
}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_STAR_EATEN:
		score_ += mngr_->getComponent<Points>(m.star_eaten_data.e)->points_;
		break;
	default:
		break;
	}
}
