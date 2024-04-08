#include "FoodSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/InmuneComponent.h"
#include "../components/MiraculousComponent.h"

FoodSystem::FoodSystem() :
	cols_(8), fils_(6)
{

};

void FoodSystem::initSystem() {

}

void FoodSystem::update()
{
	auto fruits = mngr_->getEntities(ecs::grp::FRUITS);
	for (auto e : fruits)
	{
		auto eMir = mngr_->getComponent<MiraculousComponent>(e);
		if (eMir != nullptr) {
			// Convertir en milagrosa
			if (!eMir->getIsMiracle() && (sdlutils().virtualTimer().currTime() - eMir->timeToConvert) >= eMir->nTime)
			{
				eMir->setMiraculous(); // Convierte en miraculosa
				mngr_->getComponent<ImageWithFrames>(e)->changeFirstLastFrame(13, 13); // Cambia la imagen
			}
			// convertir en normal
			else if (eMir->getIsMiracle() && (sdlutils().virtualTimer().currTime() - eMir->timeToDesConvert) >= eMir->mTime)
			{
				eMir->resetMiraculous(); // Convierte en normal
				mngr_->getComponent<ImageWithFrames>(e)->changeFirstLastFrame(12, 12); // Cambia la imagen
			}
		}
	}
}

void FoodSystem::eatFruit(ecs::entity_t fruit) {
	auto pc = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pcInm = mngr_->getComponent<InmuneComponent>(pc);
	auto fMir = mngr_->getComponent<MiraculousComponent>(fruit);

	if (fMir != nullptr && fMir->getIsMiracle())
	{
		pcInm->setInmune(true);
		Message m;
		m.id = _m_IMMUNITY_START;
		mngr_->send(m);
	}

	mngr_->setAlive(fruit, false);
	sdlutils().soundEffects().at("pacman_eat").play(0, 1); // Sonido del Pacman comiendo.

	auto fruits = mngr_->getEntities(ecs::grp::FRUITS);

	if (fruits.size() <= 0) {
		Message m;
		m.id = _m_ROUND_WIN;
		mngr_->send(m);
	}
}

void FoodSystem::setFruits() {

	for (int i = 0; i < cols_; i++)
	{
		for (int j = 0; j < fils_; j++)
		{
			// Aniade fruta
			auto e = mngr_->addEntity(ecs::grp::FRUITS);
			auto tr = mngr_->addComponent<Transform>(e);

			uint16_t p = sdlutils().rand().nextInt(0, 10);
			if (p == 0)
			{
				uint16_t n = sdlutils().rand().nextInt(10, 21);
				//std::cout << "Fruta milagrosa" << std::endl;
				mngr_->addComponent<MiraculousComponent>(e, n);
			}

			// Asigna posicion
			tr->width_ = 40;
			tr->height_ = 40;
			tr->pos_ = Vector2D(i + 0.5, j + 0.5) * 95;

			auto img = mngr_->addComponent<ImageWithFrames>(e, &sdlutils().images().at("pacman_spritesheet"), 8, 8, 12, 12);
		}
	}
}
void FoodSystem::resetFruits() {
	// Elimina entidades
	deleteFruits();
	// Settea frutas
	setFruits();
}

void FoodSystem::deleteFruits()
{
	auto fruits = mngr_->getEntities(ecs::grp::FRUITS);
	for (auto e : fruits)
	{
		mngr_->setAlive(e, false);
	}
}

void FoodSystem::recieve(const Message& m) {
	switch (m.id)
	{
	case _m_PACMAN_FOOD_COLLISION:
		eatFruit(m.ent_collided.e);
		break;
	case _m_NEW_GAME:
		resetFruits();
		break;
	default:
		break;
	}
}

