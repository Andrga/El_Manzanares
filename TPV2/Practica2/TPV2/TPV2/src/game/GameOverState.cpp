#include "GameOverState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

GameOverState::GameOverState() {

}

GameOverState::~GameOverState() {

}

void GameOverState::enter() 
{
	std::cout << "Enter GameOverState." << std::endl;
}

void GameOverState::update() 
{
	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::NEWGAME);
	}
}

void GameOverState::leave() 
{
	std::cout << "Leave GameOverState." << std::endl;
}