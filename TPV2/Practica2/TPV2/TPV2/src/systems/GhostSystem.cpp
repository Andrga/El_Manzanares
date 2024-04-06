#include "GhostSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GhostMotion.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem(int ghostLimit): ghostLimit_(ghostLimit)
{
}

void GhostSystem::initSystem()
{
	generateGhost();
}

void GhostSystem::update()
{
	auto currTime = sdlutils().currRealTime();
	// Coge todos los fantasmas
	auto ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	auto n = ghosts.size();

	// Coge el pacman y su posicion del pacman
	auto p = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto posPM = mngr_->getComponent<Transform>(p)->pos_;

	// Actualizacion de la posicion de los fantasmas
	for (auto g : ghosts) {
		if (mngr_->getComponent<GhostMotion>(g)->shouldUpdate(currTime)) {
			mngr_->getComponent<Transform>(g)->vel_ = (posPM - mngr_->getComponent<Transform>(g)->pos_).normalize() * 1.1f;
		}
	}
}

void GhostSystem::generateGhost()
{
	auto e = mngr_->addEntity(ecs::grp::GHOSTS);
	mngr_->addComponent<Transform>(e);
	mngr_->addComponent<GhostMotion>(e);
	// add an Image Component
	mngr_->addComponent<Image>(e, &sdlutils().images().at("star"));

}
