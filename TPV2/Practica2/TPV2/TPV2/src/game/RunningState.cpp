#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

// Includes de los sistemas
#include "../systems/CollisionsSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/StarsSystem.h"

RunningState::RunningState(){

}

RunningState::~RunningState() {

}

void RunningState::enter()
{
	std::cout << "Enter RunningState." << std::endl;

	// Traemos los sistemas.
	collisionsSystem = Game::instance()->getMngr()->getSystem<CollisionsSystem>();
	gameCtrlSystem = Game::instance()->getMngr()->getSystem<GameCtrlSystem>();
	ghostSystem = Game::instance()->getMngr()->getSystem<GhostSystem>();
	pacManSystem = Game::instance()->getMngr()->getSystem<PacManSystem>();
	renderSystem = Game::instance()->getMngr()->getSystem<RenderSystem>();
	starsSystem = Game::instance()->getMngr()->getSystem<StarsSystem>();
}

void RunningState::update() {
	// Pausa.
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_P))
	{
		Game::instance()->setState(Game::PAUSED);
	}

	// Llama a los updates de los sistemas:
	collisionsSystem->update();
	gameCtrlSystem->update();
	ghostSystem->update();
	pacManSystem->update();
	renderSystem->update();
	starsSystem->update();

	//Game::instance()->getMngr()->refresh(); // Esta en el bucle principal.
}

void RunningState::leave()
{
	std::cout << "Leave RunningState." << std::endl;

}