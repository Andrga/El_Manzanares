// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "PauseState.h"
#include "GameOverState.h"

using ecs::Manager;

Game::Game() :
	mngr_(), //
	pacmanSys_(), //
	gameCtrlSys_(), //
	startsSys_(), //
	renderSys_(), //
	collisionSys_(),
	newgame_state_(nullptr),
	newround_state_(nullptr),
	running_state_(nullptr),
	paused_state_(nullptr),
	gameover_state_(nullptr)
{

}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();

	// add the systems
	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	startsSys_ = mngr_->addSystem<StarsSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();
	ghostSys_ = mngr_->addSystem<GhostSystem>();
	foodSys_ = mngr_->addSystem<FoodSystem>();

	// Estados:
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	running_state_ = new RunningState();
	paused_state_ = new PauseState();
	gameover_state_ = new GameOverState();

	current_state_ = newgame_state_;
	current_state_->enter();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto& ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		current_state_->update();


		/*pacmanSys_->update();
		startsSys_->update();
		gameCtrlSys_->update();
		collisionSys_->update();
		ghostSys_->update();*/

		mngr_->refresh();

		sdlutils().clearRenderer();
		renderSys_->update(); // Esto tiene que estar aqui?
		sdlutils().presentRenderer();

		// Para enviar los mensajes.
		mngr_->flushMessagesWithSwap();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

