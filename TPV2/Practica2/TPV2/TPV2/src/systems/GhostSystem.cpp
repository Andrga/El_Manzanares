#include "GhostSystem.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GhostMotion.h"
#include "../components/InmuneComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem(int ghostLimit) :
	ghostLimit_(ghostLimit), currentGhosts_(0), maxSpawnTime_(2000)
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
	if (maxSpawnTime_ + currentTime_ < sdlutils().virtualTimer().currTime() && currentGhosts_ < ghostLimit_) {

		currentTime_ = sdlutils().virtualTimer().currTime();

		// Crea entidad fantasma con sus componentes
		auto e = mngr_->addEntity(ecs::grp::GHOSTS);
		auto tr = mngr_->addComponent<Transform>(e);
		mngr_->addComponent<GhostMotion>(e);
		mngr_->addComponent<Image>(e, &sdlutils().images().at("star"));

		// Tamanio al transform
		tr->width_ = 30;
		tr->height_ = 30;

		// Esquina en la que va a spawnear el fantasma
		int spawnEsquina = sdlutils().rand().nextInt(0, 4);

		switch (spawnEsquina)
		{
		case 1: // Arriba derecha
			tr->pos_ = Vector2D(sdlutils().width() - tr->height_, 0);
			break;
		case 2: // Abajo izquierda
			tr->pos_ = Vector2D(0, sdlutils().height() - tr->height_);
			break;
		case 3: // Abajo derecha
			tr->pos_ = Vector2D(sdlutils().width() - tr->height_, sdlutils().height() - tr->height_);
			break;
		default: // Arriba izquierda
			tr->pos_ = Vector2D(0, 0);
			break;
		}


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
			auto gt = mngr_->getComponent<Transform>(g);
			// Settea velocidad del fantasma
			mngr_->getComponent<Transform>(g)->vel_ = (posPM->pos_ - gt->pos_).normalize() * 1.1f;

			// Actualiza la posicion del fantasma
			gt->pos_ = gt->pos_ + gt->vel_;

			// Debug
			//std::cout << gt->pos_ << std::endl;
		}
	}
}

void GhostSystem::collGhost(ecs::entity_t ghost)
{
	auto p = mngr_->getHandler(ecs::hdlr::PACMAN);
	if (mngr_->getComponent<InmuneComponent>(p)->getImmunity()) {

		Message m;
		m.id = _m_ROUND_OVER;
		sdlutils().soundEffects().at("pacman_eat").play(0, 1);
	}
	else
	{
		mngr_->setAlive(ghost, false);
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

void GhostSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		collGhost(m.ent_collided.e);
		break;
	case _m_ROUND_START:
		resetGhosts();
		break;
	default:
		break;
	}
}
