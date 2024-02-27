// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameInfoMsgs.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameState.h"

GameInfoMsgs::GameInfoMsgs() :
		gameState_(nullptr) {

}

GameInfoMsgs::~GameInfoMsgs() {
	// TODO Auto-generated destructor stub
}

void GameInfoMsgs::initComponent() {
	gameState_ = mngr_->getComponent<GameState>(ent_);
	assert(gameState_ != nullptr);
}

void GameInfoMsgs::render() {

	auto state = gameState_->getState();

	// message when game is not running
	if (state != GameState::RUNNING) {

		// game over message
		if (state == GameState::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state == GameState::NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}

	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(gameState_->getScore(0)) + " - "
					+ std::to_string(gameState_->getScore(1)),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}
