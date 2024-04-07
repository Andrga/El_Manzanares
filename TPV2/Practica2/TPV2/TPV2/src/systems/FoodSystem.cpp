#include "FoodSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"

FoodSystem::FoodSystem() :
	cols_(8), fils_(6)
{

};

void FoodSystem::initSystem() {
	for (int i = 0; i < cols_; i++)
	{
		for (int j = 0; j < fils_; j++)
		{
			// Aniade fruta
			auto e = mngr_->addEntity(ecs::grp::FRUITS);
			auto tr = mngr_->addComponent<Transform>(e);

			// Asigna posicion
			tr->width_ = 40;
			tr->height_ = 40;
			tr->pos_ = Vector2D(i + 0.5, j + 0.5) * 95;

			auto img = mngr_->addComponent<ImageWithFrames>(e, &sdlutils().images().at("pacman_spritesheet"), 8, 8, 12, 12);
		}
	}
};
void FoodSystem::eatFruit(ecs::entity_t fruit) {
	mngr_->setAlive(fruit, false);

	auto fruits = mngr_->getEntities(ecs::grp::FRUITS);

	if (fruits.size() <= 0) {
		Message m;
		m.id = _m_ROUND_WIN;
		sdlutils().soundEffects().at("pacman_eat").play(0, 1);
	}
}

void FoodSystem::recieve(const Message& m) {
	switch (m.id)
	{
	case _m_PACMAN_FOOD_COLLISION:
		eatFruit(m.ent_collided.e);
		break;

	default:
		break;
	}
}

