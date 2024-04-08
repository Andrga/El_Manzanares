#include "PauseState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
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
		// Mensaje para despausar el juego.
		Message message;
		message.id = _m_UNPAUSE_GAME;
		Game::instance()->getMngr()->send(message, true);
	}
	messageTexture->render(messageRect);
}

void PauseState::leave() 
{
	std::cout << "Leave PauseState.\n" << std::endl;

	sdlutils().virtualTimer().resume(); // Volver a poner el tiempo.
}