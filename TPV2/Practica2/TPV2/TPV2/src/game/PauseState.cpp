#include "PauseState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

PauseState::PauseState() : ihdlr(ih())

{}

PauseState::~PauseState() {

}

void PauseState::enter() {
	sdlutils().virtualTimer().pause(); // Pausa el tiempo.
}

void PauseState::update() {
	if (ih().keyDownEvent())
	{
		
	}
}

void PauseState::leave() {

}