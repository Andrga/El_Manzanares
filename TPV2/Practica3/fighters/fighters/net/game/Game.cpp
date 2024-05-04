// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "Bullets.h"
#include "Fighter.h"
#include "Networking.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

Game::Game() :
		bm_(nullptr), //
		fighters_(nullptr), //
		net_(nullptr) {
}

Game::~Game() {
	delete fighters_;
	delete bm_;
}

bool Game::init(char *host, Uint16 port) {

	net_ = new Networking();

	if (!net_->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
	}
	std::cout << "Connected as client " << (int) net_->client_id() << std::endl;

	// initialize the SDLUtils singleton
	SDLUtils::init("SDLNet Game", 900, 480,
			"resources/config/asteroid.resources.json");

	bm_ = new Bullets();
	fighters_ = new Fighter();

	// add some players
	fighters_->addPlayer(net_->client_id());

	return true;
}

void Game::start() {
	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();
		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_R)) {
				net_->send_restart();
			}

		}

		fighters_->update();
		bm_->update();
		net_->update();

		check_collisions();

		sdlutils().clearRenderer();

		fighters_->render();
		bm_->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	net_->disconnect();

}

void Game::check_collisions() {
	if (!net_->is_master())
		return;

	for (Bullets::Bullet &b : *bm_) {
		if (b.used) {
			for (Fighter::Player &p : *fighters_) {
				if (p.state == Fighter::ALIVE) {
					if (Collisions::collidesWithRotation(p.pos, p.width,
							p.height, p.rot, b.pos, b.width, b.height, b.rot)) {

						net_->send_dead(p.id);
						continue;
					}
				}
			}
		}
	}
}
