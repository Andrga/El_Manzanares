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

			std::cout << "LA PUTA MADRE" << std::endl;
			tr->width_ = 40;
			tr->height_ = 40;
			tr->pos_ = Vector2D(i + 0.5, j + 0.5) * 95;

			auto img = mngr_->addComponent<ImageWithFrames>(e, &sdlutils().images().at("pacman_spritesheet"), 8, 8, 12, 12);
		}
	}
};

