#include "PauseState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

#include "../systems/CollisionsSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"

PauseState::PauseState() : ihdlr(ih())
{
	messageTexture = &sdlutils().msgs().at("pause");

	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,
		(sdlutils().height() - messageTexture->height()) / 2,
		messageTexture->width(),
		messageTexture->height());
}

PauseState::~PauseState() {

}

void PauseState::enter() 
{
	std::cout << "Enter PauseState." << std::endl;

	sdlutils().virtualTimer().pause(); // Pausar el tiempo.
}

void PauseState::update() 
{
	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::RUNNING);
	}
	messageTexture->render(messageRect);
}

void PauseState::leave() 
{
	std::cout << "Leave PauseState." << std::endl;

	sdlutils().virtualTimer().resume(); // Volver a poner el tiempo.
}