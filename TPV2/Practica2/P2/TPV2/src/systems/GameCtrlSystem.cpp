// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../sdlutils/InputHandler.h"
#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

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
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {

			/* Manda mensaje
			Message m;
			m.id = _m_CREATE_STARS;
			m.create_stars_data.n = 5;
			mngr_->send(m);*/
		}
	}
}

void GameCtrlSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_NEW_GAME:
		setScore(0); // Para resetear los puntos al inicio de un nuevo juego.
		break;
	case _m_GAME_OVER:
		Game::instance()->setState(Game::GAMEOVER);
		break;
	case _m_ROUND_OVER:
		Game::instance()->setState(Game::NEWROUND);
		break;
	case _m_WIN_GAME:
		Game::instance()->setState(Game::GAMEOVER);
		break;
	case _m_ROUND_START:
		Game::instance()->setState(Game::RUNNING);
		break;
	case _m_PAUSE_GAME:
		Game::instance()->setState(Game::PAUSED);
		break;
	case _m_UNPAUSE_GAME:
		Game::instance()->setState(Game::RUNNING);
		break;
	case _m_FRUIT_EAT:
		incrScore(mngr_->getComponent<Points>(m.ent_collided.e)->points_);
		break;
	case _m_GHOST_EAT:
		incrScore(mngr_->getComponent<Points>(m.ent_collided.e)->points_);
		break;
	default:
		break;
	}
}