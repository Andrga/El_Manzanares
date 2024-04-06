#include "GhostSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GhostMotion.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem(int ghostLimit) : ghostLimit_(ghostLimit)
{
}

void GhostSystem::initSystem()
{

}

void GhostSystem::update()
{
	generateGhost();

	auto currTime = sdlutils().currRealTime();
	// Coge todos los fantasmas
	auto ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	auto n = ghosts.size();

	// Coge el pacman y su posicion del pacman
	auto p = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto posPM = mngr_->getComponent<Transform>(p);

	// Actualizacion de la posicion de los fantasmas
	for (int i = 0; i < n; i++) {
		/*if (mngr_->getComponent<GhostMotion>(g)->shouldUpdate(currTime))
		{
			mngr_->getComponent<Transform>(g)->vel_ = (posPM->pos_ - mngr_->getComponent<Transform>(g)->pos_).normalize() * 5.0f;

		}*/
		// coge el transform del pacman
		auto PM = mngr_->getHandler(ecs::hdlr::PACMAN);
		auto posPM = mngr_->getComponent<Transform>(PM);

		auto gt = mngr_->getComponent<Transform>(ghosts[i]);
		// modifica la velocidad del ghost con respecto de la del pacman
		gt->vel_ = (posPM->pos_ - gt->pos_).normalize() * 1.1f;
		//gt->vel_ = Vector2D(50.0f, 50.0f);
		//std::cout << gt->vel_;
		//gt->update();

		// move the pacman
		gt->pos_ = gt->pos_ + gt->vel_;
	}
}

void GhostSystem::generateGhost()
{
	if (currentGhosts_ < ghostLimit_) {
		auto e = mngr_->addEntity(ecs::grp::GHOSTS);
		auto tr = mngr_->addComponent<Transform>(e);
		mngr_->addComponent<GhostMotion>(e);
		// add an Image Component
		mngr_->addComponent<Image>(e, &sdlutils().images().at("star"));

		tr->width_ = 30;
		tr->height_ = 30;

		currentGhosts_++;
	}
}
