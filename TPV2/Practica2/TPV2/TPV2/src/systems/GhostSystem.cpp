#include "GhostSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GhostMotion.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem(int ghostLimit) :
	ghostLimit_(ghostLimit), currentGhosts_(0)
{
}

void GhostSystem::initSystem()
{

}

void GhostSystem::update()
{
	generateGhost();
	moveGhosts();
}

void GhostSystem::generateGhost()
{
	// Si no se ha llegado al limite de fantasmas se generan
	if (currentGhosts_ < ghostLimit_) {
		// Crea entidad fantasma con sus componentes
		auto e = mngr_->addEntity(ecs::grp::GHOSTS);
		auto tr = mngr_->addComponent<Transform>(e);
		mngr_->addComponent<GhostMotion>(e);
		mngr_->addComponent<Image>(e, &sdlutils().images().at("star"));

		// Tamanio al transform
		tr->width_ = 30;
		tr->height_ = 30;

		// Aumenta el contador de fantasmas
		currentGhosts_++;
	}
}

void GhostSystem::moveGhosts()
{
	auto currTime = sdlutils().currRealTime();

	// Coge todos los fantasmas
	auto ghosts = mngr_->getEntities(ecs::grp::GHOSTS);

	// Coge el pacman y su posicion del pacman
	auto p = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto posPM = mngr_->getComponent<Transform>(p);

	// Actualizacion de la posicion de los fantasmas
	for (auto& g : ghosts) {
		if (mngr_->getComponent<GhostMotion>(g)->shouldUpdate(currTime))
		{

			// Settea velocidad del fantasma
			mngr_->getComponent<Transform>(g)->vel_ = (posPM->pos_ - mngr_->getComponent<Transform>(g)->pos_).normalize() * 5.0f;

			// Actualiza la posicion del fantasma
			posPM->pos_ = posPM->pos_ + posPM->vel_;
		}
	}
}

void GhostSystem::resetGhosts()
{
	auto ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	for (auto e : ghosts)
	{
		mngr_->setAlive(e, false);
	}
	currentGhosts_ = 0;
}
