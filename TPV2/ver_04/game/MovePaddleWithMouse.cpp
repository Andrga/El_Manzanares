// This file is part of the course TPV2@UCM - Samir Genaim

#include "MovePaddleWithMouse.h"

#include "../sdlutils/InputHandler.h"
#include "Container.h"

MovePaddleWithMouse::MovePaddleWithMouse() {
}

MovePaddleWithMouse::~MovePaddleWithMouse() {
}

void MovePaddleWithMouse::handleInput(Container *o) {
	auto &ihdlr = ih();
	if (ihdlr.mouseMotionEvent()) {
		o->getPos().setY(ihdlr.getMousePos().second);
	}
}
