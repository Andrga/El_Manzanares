#include "GameOverState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/LifeComponent.h"
#include "../ecs/Manager.h"
#include "Game.h"

GameOverState::GameOverState() {

}

GameOverState::~GameOverState() {

}

void GameOverState::enter()
{
	std::cout << "Enter GameOverState." << std::endl;

	auto pacManEnt = Game::instance()->getMngr()->getEntities(ecs::hdlr::PACMAN);
	pacMan = *pacManEnt.begin();

	if (Game::instance()->getMngr()->getComponent<LifeComponent>(pacMan)->getActualLifes() > 0)
	{
		messageTexture = &sdlutils().msgs().at("gameoverLost");
		std::cout << "Has perdido." << std::endl;
	}
	else
	{
		messageTexture = &sdlutils().msgs().at("gameoverWin");
		std::cout << "Has ganado." << std::endl;
	}

	messageRect = build_sdlrect((sdlutils().width() - messageTexture->width()) / 2,
		(sdlutils().height() - messageTexture->height()) / 2,
		messageTexture->width(),
		messageTexture->height());
}

void GameOverState::update()
{

	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::NEWGAME);
	}
}

void GameOverState::leave()
{
	sdlutils().virtualTimer().resume();
	std::cout << "Leave GameOverState." << std::endl;
}