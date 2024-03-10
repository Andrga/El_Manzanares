// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "BlackHoleFacade.h"
#include "MissileFacade.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade* ast_mngr,
	FighterFacade* fighter_mngr, BlackHoleFacade* hole_manager, MissileFacade* mis_manager) :
	ihdlr(ih()), //
	ast_mngr_(ast_mngr), //
	fighter_mngr_(fighter_mngr), //
	hole_mngr_(hole_manager), // Manager de los Blackholes
	missile_manager(mis_manager),
	lastTimeGeneratedAsteroids_() {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto& asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto& holes = mngr->getEntities(ecs::grp::HOLES);
	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);

	//------UPDATE:
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}
	for (auto h : holes) { // Update de los agujeros negros
		mngr->update(h);
	}
	for (auto m : missiles) { // Update de los miSssssileSss.
		mngr->update(m);
	}
	for (auto m : missiles)
	{
		// Actualizacion de la rotacion del misil.
		auto missileTransform = mngr->getComponent<Transform>(m); // Transform del misil.
		auto missileVelocity = missileTransform->getVel(); // Velocidad del misil.
		float newRotation = Vector2D(0, -1).angle(missileVelocity); // Actualizamos la rotacion del misil.
		missileTransform->setRot(newRotation);
		// Comprobacion de salida de limites de la pantalla.
		int missileX = missileTransform->getPos().getX();
		int missileY = missileTransform->getPos().getY();
		if (missileX < 0 || missileX > sdlutils().width() || missileY < 0 || missileY > sdlutils().height()) {
			mngr->setAlive(m, false);
			std::cout << "\nMisil fuera de rango.\n";
		}
	}

	// check collisions
	checkCollisions();

	//------RENDER:
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto h : holes) { // Render de los agujeros negros
		mngr->render(h);
	}
	for (auto m : missiles) { // Render de los misiles.
		mngr->render(m);
	}
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto& asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto& blackholes = mngr->getEntities(ecs::grp::HOLES);
	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto num_of_asteroids = asteroids.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			aTR->getPos(), //
			aTR->getWidth(), //
			aTR->getHeight(), //
			aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
					b.pos, //
					b.width, //
					b.height, //
					b.rot, //
					aTR->getPos(), //
					aTR->getWidth(), //
					aTR->getHeight(), //
					aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

		// BlackHoles with asteroids
		for (auto& h : blackholes) {
			auto bhTrans = mngr->getComponent<Transform>(h);
			if (Collisions::collidesWithRotation( //
				bhTrans->getPos(), //
				bhTrans->getWidth(), //
				bhTrans->getHeight(), //
				bhTrans->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
				ast_mngr_->move_asteroid(a);
				continue;

			}
		}
	}

	//-----Colisiones con los misiles:
	auto num_of_missiles = missiles.size();
	for (size_t i = 0u; i < num_of_missiles; i++)
	{
		auto missile = asteroids[i];
		if (!mngr->isAlive(missile)) {
			continue;
		}

		//----MISILES CON NAVE:
		auto missileTR = mngr->getComponent<Transform>(missile);
		if (Collisions::collidesWithRotation(
			fighterTR->getPos(), fighterTR->getWidth(), fighterTR->getHeight(), fighterTR->getRot(),
			missileTR->getPos(), missileTR->getWidth(), missileTR->getHeight(), missileTR->getRot())) 
		{
			std::cout << "\nMisil pum nave.\n";
			onFigherDeath();
			return;
		}

		//----MISILES CON BALAS:
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation(
					b.pos, b.width, b.height, b.rot,
					missileTR->getPos(), missileTR->getWidth(), missileTR->getHeight(), missileTR->getRot())) 
				{
					//ast_mngr_->split_astroid(a);
					std::cout << "\nMisil pum bala.\n";
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}
	}

	// blackholes
	auto num_of_blackholes = blackholes.size();
	for (auto i = 0; i < num_of_blackholes; i++) {
		if (!mngr->isAlive(blackholes[i]))
			continue;

		// blackhole with fighter
		auto transformBH = mngr->getComponent<Transform>(blackholes[i]);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			transformBH->getPos(), //
			transformBH->getWidth(), //
			transformBH->getHeight(), //
			transformBH->getRot())) {
			onFigherDeath();
			return;
		}
	}
}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
