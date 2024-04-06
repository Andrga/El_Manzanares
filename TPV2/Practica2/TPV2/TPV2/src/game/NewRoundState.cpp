#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"

NewRoundState::NewRoundState()
{
	messageTexture = &sdlutils().msgs().at("newround");

	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,
		(sdlutils().height() - messageTexture->height()) / 2,
		messageTexture->width(),
		messageTexture->height());
}

NewRoundState::~NewRoundState() {

}

void NewRoundState::enter() 
{
	std::cout << "Enter NewRoundState." << std::endl;
}

void NewRoundState::update()
{
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::instance()->setState(Game::RUNNING);
		
		Message message;
		message.id = _m_ROUND_START;
		Game::instance()->getMngr()->send(message, true);
	}
	messageTexture->render(messageRect);
}

void NewRoundState::leave() 
{
	std::cout << "Leave NewRoundState." << std::endl;
}