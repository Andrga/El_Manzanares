// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include "../sdlutils/InputHandler.h"
#include "GameManager.h"

GameCtrl::GameCtrl() {
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::handleInput(Container *o) {

	auto gm = static_cast<GameManager*>(o);
	auto state_ = gm->getState();
	if (state_ != GameManager::RUNNING) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case GameManager::NEWGAME:
				gm->moveBall();
				gm->setState(GameManager::RUNNING);
				break;
			case GameManager::PAUSED:
				gm->moveBall();
				gm->setState(GameManager::RUNNING);
				break;
			case GameManager::GAMEOVER:
				gm->setState(GameManager::NEWGAME);
				gm->setScore(0, 0);
				gm->setScore(1, 0);
				break;
			default:
				break;
			}
		}
	}

}
