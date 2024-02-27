// This file is part of the course TPV2@UCM - Samir Genaim

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "GameState.h"
#include "Transform.h"
GameState::GameState() :
		score_(), //
		state_(NEWGAME), //
		maxScore_(5), //
		ballTr_(nullptr) {
}

GameState::~GameState() {
}

void GameState::initComponent() {
	auto ball = mngr_->getHandler(ecs::hdlr::BALL);
	ballTr_ = mngr_->getComponent<Transform>(ball);
	assert(ballTr_ != nullptr);
}

void GameState::update() {
	if (state_ != RUNNING) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
				moveBall();
				setState(RUNNING);
				break;
			case PAUSED:
				moveBall();
				setState(RUNNING);
				break;
			case GAMEOVER:
				setState(NEWGAME);
				setScore(0, 0);
				setScore(1, 0);
				break;
			default:
				break;
			}
		}
	}
}

void GameState::onBallExit(Side side) {

	assert(state_ == RUNNING); // this should be called only when game is running

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}
	resetBall();
	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		state_ = PAUSED;
	else
		state_ = GAMEOVER;
}

void GameState::resetBall() {
	ballTr_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ballTr_->getVel().set(0, 0);
}

void GameState::moveBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
	ballTr_->getVel().set(v.normalize() * 2);
}
