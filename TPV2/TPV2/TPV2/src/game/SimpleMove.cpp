// This file is part of the course TPV2@UCM - Samir Genaim

#include "SimpleMove.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

SimpleMove::SimpleMove() {

}

SimpleMove::~SimpleMove() {
}

void SimpleMove::update(Container *o) {

	auto &pos = o->getPos();
	auto &vel = o->getVel();

	pos = pos + vel;

}
