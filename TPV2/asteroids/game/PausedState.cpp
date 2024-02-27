// This file is part of the course TPV2@UCM - Samir Genaim

#include "PausedState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

PausedState::PausedState() :
		msg_(sdlutils().msgs().at("paused")), //
		ihdlr(ih()) {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

PausedState::~PausedState() {
}

void PausedState::enter() {
	sdlutils().virtualTimer().pause();
}

void PausedState::leave() {
	sdlutils().virtualTimer().resume();
}

void PausedState::update() {
	if (ihdlr.keyDownEvent()) {
		Game::instance()->setState(Game::RUNNING);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

