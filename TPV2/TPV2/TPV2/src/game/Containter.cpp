// This file is part of the course TPV2@UCM - Samir Genaim

#include "Container.h"

#include "../sdlutils/macros.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

Container::Container() {
}

Container::~Container() {
	for (auto pc : pc_)
		delete pc;

	for (auto rc : rc_)
		delete rc;

	for (auto ic : ic_)
		delete ic;
}

void Container::update() {
	for (auto pc : pc_)
		pc->update(this);

}

void Container::render() {
	for (auto rc : rc_)
		rc->render(this);
}

void Container::handleInput() {
	for (auto ic : ic_)
		ic->handleInput(this);
}
