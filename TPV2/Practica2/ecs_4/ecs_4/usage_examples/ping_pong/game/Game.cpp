// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/BallSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PaddlesSystem.h"
#include "../systems/RenderSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		mngr_(nullptr), //
		ballSys_(nullptr), //
		paddlesSys_(nullptr), //
		gameCtrlSys_(nullptr), //
		collisionsSys_(nullptr), //
		renderSys_(nullptr) {
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// Initialize the SDLUtils singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	sdlutils().hideCursor();

	// Create the manager
	mngr_ = new Manager();

	ballSys_ = mngr_->addSystem<BallSystem>();
	paddlesSys_ = mngr_->addSystem<PaddlesSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	collisionsSys_ = mngr_->addSystem<CollisionsSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->refresh();

		ballSys_->update();
		paddlesSys_->update();
		collisionsSys_->update();
		gameCtrlSys_->update();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}
