// This file is part of the course TPV2@UCM - Samir Genaim

#include "InfoMsgs.h"

#include "../sdlutils/SDLUtils.h"

#include "GameManager.h"

InfoMsgs::InfoMsgs() {
}

InfoMsgs::~InfoMsgs() {
}

void InfoMsgs::render(Container *o) {
	auto gm = static_cast<GameManager*>(o);

	auto state = gm->getState();

	// message when game is not running
	if (state != GameManager::RUNNING) {

		// game over message
		if (state == GameManager::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state == GameManager::NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}
}
