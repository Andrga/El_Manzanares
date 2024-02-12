// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/PacManCtrl.h"
#include "../components/StopOnBorders.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		mngr_(nullptr) {
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();

	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);
	auto tr = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	mngr_->addComponent<PacManCtrl>(pacman);
	mngr_->addComponent<StopOnBorders>(pacman);

	// create the game info entity
	auto ginfo = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::GAMEINFO, ginfo);
	mngr_->addComponent<GameCtrl>(ginfo);
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

		mngr_->update();
		mngr_->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {

	// the PacMan's Transform
	//
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pTR = mngr_->getComponent<Transform>(pacman);

	// the GameCtrl component
	auto ginfo = mngr_->getHandler(ecs::hdlr::GAMEINFO);
	auto gctrl = mngr_->getComponent<GameCtrl>(ginfo);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &stars = mngr_->getEntities(ecs::grp::STARS);
	auto n = stars.size();
	for (auto i = 0u; i < n; i++) {
		auto e = stars[i];
		if (mngr_->isAlive(e)) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = mngr_->getComponent<Transform>(e);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(pTR->getPos(), pTR->getWidth(),
					pTR->getHeight(), //
					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
				mngr_->setAlive(e, false);
				gctrl->onStarEaten();

				// play sound on channel 1 (if there is something playing there
				// it will be cancelled
				sdlutils().soundEffects().at("pacman_eat").play(0, 1);
			}
		}
	}
}
