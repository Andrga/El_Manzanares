// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	//
	auto pm = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pTR = mngr_->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &fruits = mngr_->getEntities(ecs::grp::FRUITS);
	auto f = fruits.size();
	for (auto i = 0u; i < f; i++) {
		auto e = fruits[i];
		if (mngr_->isAlive(e)) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = mngr_->getComponent<Transform>(e);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(			//
					pTR->pos_, pTR->width_, pTR->height_, //
					eTR->pos_, eTR->width_, eTR->height_)) {

				//std::cout << "Colision fruta" << std::endl;
				Message m;
				m.id = _m_PACMAN_FOOD_COLLISION;
				m.ent_collided.e = e;
				mngr_->send(m);

			}
		}
	}


	// Colisiones con los fantasmas
	auto& ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	auto g = ghosts.size();
	for (auto i = 0u; i < g; i++) {
		auto e = ghosts[i];
		if (mngr_->isAlive(e)) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = mngr_->getComponent<Transform>(e);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(			//
				pTR->pos_, pTR->width_, pTR->height_, //
				eTR->pos_, eTR->width_, eTR->height_)) {

				//std::cout << "Colision Fantasma" << std::endl;
				Message m;
				m.id = _m_PACMAN_GHOST_COLLISION;
				m.ent_collided.e = e;
				mngr_->send(m);
			}
		}
	}
}