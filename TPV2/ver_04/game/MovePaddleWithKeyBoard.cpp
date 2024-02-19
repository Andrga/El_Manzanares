// This file is part of the course TPV2@UCM - Samir Genaim

#include "MovePaddleWithKeyBoard.h"

#include "../sdlutils/InputHandler.h"
#include "Container.h"

MovePaddleWithKeyBoard::MovePaddleWithKeyBoard() :
		up_(SDL_SCANCODE_UP), //
		down_(SDL_SCANCODE_DOWN), //
		stop_(SDL_SCANCODE_LEFT), //
		speed_(10.0f) //
{
}

MovePaddleWithKeyBoard::~MovePaddleWithKeyBoard() {
}

void MovePaddleWithKeyBoard::handleInput(Container *o) {
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(up_)) {
			o->getVel().setY(-speed_);
		} else if (ihdlr.isKeyDown(down_)) {
			o->getVel().setY(speed_);
		} else if (ihdlr.isKeyDown(stop_)) {
			o->getVel().setY(0.0f);
		}
	}
}
