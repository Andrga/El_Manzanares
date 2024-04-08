#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

// Includes de los sistemas
#include "../systems/CollisionsSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"

RunningState::RunningState() {

}

RunningState::~RunningState() {

}

void RunningState::enter()
{
	std::cout << "Enter RunningState." << std::endl;

	sdlutils().soundEffects().at("pacman_chomp").play(-1); // Sonido del movimiento del Pacman. Suena un poco rarete.

	// Traemos los sistemas.
	collisionsSystem = Game::instance()->getMngr()->getSystem<CollisionsSystem>();
	foodSystem = Game::instance()->getMngr()->getSystem<FoodSystem>();
	gameCtrlSystem = Game::instance()->getMngr()->getSystem<GameCtrlSystem>();
	ghostSystem = Game::instance()->getMngr()->getSystem<GhostSystem>();
	immunitySystem = Game::instance()->getMngr()->getSystem<ImmunitySystem>();
	pacManSystem = Game::instance()->getMngr()->getSystem<PacManSystem>();
	renderSystem = Game::instance()->getMngr()->getSystem<RenderSystem>();
}

void RunningState::update() {
	// Pausa.
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_P))
	{
		Game::instance()->setState(Game::PAUSED);
	}
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_I))
	{
		Message message;
		message.id = _m_IMMUNITY_START;
		Game::instance()->getMngr()->send(message, true);
	}

	// Llama a los updates de los sistemas:
	collisionsSystem->update();
	foodSystem->update();
	gameCtrlSystem->update();
	ghostSystem->update();
	immunitySystem->update();
	pacManSystem->update();
	renderSystem->update();

	//Game::instance()->getMngr()->refresh(); // Esta en el bucle principal.
}

void RunningState::leave()
{
	sdlutils().soundEffects().at("pacman_chomp").pauseChannel(); // Para parar la musica del Pacman.
	std::cout << "Leave RunningState.\n" << std::endl;

}