// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameManager.h"

#include <cassert>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "Container.h"

#include "GameObject.h"

GameManager::GameManager(GameObject *ball) :
		score_(), //
		state_(NEWGAME), //
		maxScore_(5), //
		ball_(ball) {
}

GameManager::~GameManager() {
}

void GameManager::onBallExit(Side side) {

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

void GameManager::resetBall() {
	ball_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ball_->getVel().set(0, 0);
}

void GameManager::moveBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
	ball_->getVel().set(v.normalize() * 2);
}
