// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "FighterFacade.h"
#include "Game.h"

NewGameState::NewGameState(FighterFacade *fighter_mngr) :
		msg_(sdlutils().msgs().at("newgame")), //
		ihdlr(ih()), //
		fighter_mngr_(fighter_mngr) {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewGameState::~NewGameState() {
}

void NewGameState::leave() {
}

void NewGameState::update() {
	if (ihdlr.keyDownEvent()) {
		fighter_mngr_->reset_lives();
		Game::instance()->setState(Game::NEWROUND);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewGameState::enter() {
}
