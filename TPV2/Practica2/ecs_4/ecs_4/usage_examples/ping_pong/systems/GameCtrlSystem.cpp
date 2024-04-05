// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/GameState.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "BallSystem.h"
GameCtrlSystem::GameCtrlSystem() :
		score_(), //
		state_(NEWGAME), //
		maxScore_(5) {
}

GameCtrlSystem::~GameCtrlSystem() {
}

void GameCtrlSystem::update() {
	if (state_ != RUNNING) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
				mngr_->getSystem<BallSystem>()->moveBall();
				state_ = RUNNING;
				break;
			case PAUSED:
				mngr_->getSystem<BallSystem>()->moveBall();
				state_ = RUNNING;
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				score_[0] = 0;
				score_[1] = 0;
				break;
			default:
				break;
			}
		}
	}
}

void GameCtrlSystem::onBallExit(Side side) {

	assert(state_ == RUNNING); // this should be called only when game is running

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}

	mngr_->getSystem<BallSystem>()->resetBall();

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_ = PAUSED;
	else
		state_ = GAMEOVER;
}

