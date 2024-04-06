#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

NewGameState::NewGameState() : ihdlr(ih())
{
	messageTexture = &sdlutils().msgs().at("newgame");

	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,
		(sdlutils().height() - messageTexture->height()) / 2,
		messageTexture->width(),
		messageTexture->height());
}

NewGameState::~NewGameState() {

}

void NewGameState::enter()
{
	std::cout << "Enter NewGameState." << std::endl;
}

void NewGameState::update()
{
	if (ih().keyDownEvent()) // Pulsando cualquier tecla pasa al siguiente estado.
	{
		Game::instance()->setState(Game::NEWROUND);
	}
	messageTexture->render(messageRect);
}

void NewGameState::leave()
{
	std::cout << "Leave NewGameState." << std::endl;
}