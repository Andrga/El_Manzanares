#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

// Includes de los sistemas
#include "../systems/CollisionsSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/StarsSystem.h"

RunningState::RunningState(/*CollisionsSystem* cs, GameCtrlSystem* gcs, GhostSystem* gs, PacManSystem* ps, RenderSystem* rs, StarsSystem* ss*/) /*:
	collisionsSystem(cs),
	gameCtrlSystem(gcs),
	ghostSystem(gs),
	pacManSystem(ps),
	renderSystem(rs),
	starsSystem(ss)*/

{}

RunningState::~RunningState() {

}

void RunningState::enter()
{
	std::cout << "Enter RunningState." << std::endl;
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

	//Game::instance()->getMngr()->refresh(); // Se la pela.
}

void RunningState::leave()
{
	std::cout << "Leave RunningState." << std::endl;

}