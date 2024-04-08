#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "Game.h"

NewGameState::NewGameState()
{
	messageTexture_ = &sdlutils().msgs().at("newgame");

	messageRect_ = build_sdlrect((sdlutils().width() - messageTexture_->width()) / 2,
		(sdlutils().height() - messageTexture_->height()) / 2,
		messageTexture_->width(),
		messageTexture_->height());
}

NewGameState::~NewGameState() {

}

void NewGameState::enter()
{
	std::cout << "Enter NewGameState." << std::endl;
	sdlutils().soundEffects().at("pacman_intro").play(0, 1); // Sonido de intro del juego.
}

void NewGameState::update()
{

	if (ih().keyDownEvent()) // Pulsando cualquier tecla pasa al siguiente estado.
	{
		Game::instance()->setState(Game::NEWROUND);

		// Envio del mensaje.
		Message message;
		message.id = _m_NEW_GAME;
		Game::instance()->getMngr()->send(message, true);
	}

	messageTexture_->render(messageRect_);
}

void NewGameState::leave()
{
	std::cout << "Leave NewGameState.\n" << std::endl;
}