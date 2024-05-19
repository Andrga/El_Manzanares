#include "RunningState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "Game.h"

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
		// Mensaje para pausar el juego.
		Message message;
		message.id = _m_PAUSE_GAME;
		Game::instance()->getMngr()->send(message, true);
	}
	// Para testear la inmunidad.
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_I))
	{
		// Mensaje para cuando empiece la inmunidad.
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