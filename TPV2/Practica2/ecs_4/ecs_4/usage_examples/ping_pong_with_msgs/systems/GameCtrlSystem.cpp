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
			case PAUSED:
				startRound();
				break;
			case GAMEOVER:
				startGame();
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


	if (score_[0] < maxScore_ && score_[1] < maxScore_) {
		killPacMan();
	} else {
		gameOver();
	}
}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_BALL_EXIT:
		onBallExit(static_cast<Side>(m.ball_exit.side));
		break;
	default:
		break;
	}
}

void GameCtrlSystem::startRound() {
	Message m;
	state_ = RUNNING;
	m.id = _m_ROUND_START;
	mngr_->send(m);
}

void GameCtrlSystem::startGame() {
	Message m;
	state_ = NEWGAME;
	score_[0] = 0;
	score_[1] = 0;
	m.id = _m_NEW_GAME;
	mngr_->send(m);
}

void GameCtrlSystem::killPacMan() {
	Message m;
	state_ = PAUSED;
	m.id = _m_ROUND_OVER;
	mngr_->send(m);
}

void GameCtrlSystem::gameOver() {
	Message m;
	state_ = GAMEOVER;
	m.id = _m_ROUND_OVER;
	mngr_->send(m);
	m.id = _m_GAME_OVER;
	mngr_->send(m);
}
