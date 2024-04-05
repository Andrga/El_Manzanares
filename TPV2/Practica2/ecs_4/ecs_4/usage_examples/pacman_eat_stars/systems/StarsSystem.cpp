// This file is part of the course TPV2@UCM - Samir Genaim

#include "StarsSystem.h"

#include <algorithm>
#include "../components/Image.h"
#include "../components/Points.h"
#include "../components/StarMotion.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

StarsSystem::StarsSystem() :
		starsLimit_(30), currNumOfStars_(0) {
}

StarsSystem::~StarsSystem() {
}

void StarsSystem::initSystem() {
}

void StarsSystem::update() {

	auto currTime = sdlutils().currRealTime();
	auto stars = mngr_->getEntities(ecs::grp::STARS);
	auto n = stars.size();

	for (auto i = 0u; i < n; i++) {
		auto tr = mngr_->getComponent<Transform>(stars[i]);
		auto starmotion = mngr_->getComponent<StarMotion>(stars[i]);

		if (starmotion->shouldUpdate(currTime)) {

			// rotate it
			tr->rot_ += starmotion->rot_;

			// resize it
			tr->width_ *= 0.95f;
			tr->height_ *= 0.95f;

			// check if it should die
			if (tr->width_ < starmotion->sizeLimit_
					|| tr->height_ < starmotion->sizeLimit_) {
				mngr_->setAlive(stars[i], false);
				currNumOfStars_--;
			}
		}
	}
}

void StarsSystem::addStar(unsigned int n) {

	// Always use the random number generator provided by SDLUtils
	//
	auto &rand = sdlutils().rand();

	auto limit = std::min( //
			static_cast<unsigned int>(n), //
			starsLimit_ - currNumOfStars_);

	for (auto i = 0u; i < limit; i++) {

		// add and entity to the manager
		//
		auto e = mngr_->addEntity(ecs::grp::STARS);

		// add a Transform component, and initialise it with random
		// size and position
		//
		auto tr = mngr_->addComponent<Transform>(e);
		auto s = rand.nextInt(50, 100);
		auto x = rand.nextInt(0, sdlutils().width() - s);
		auto y = rand.nextInt(0, sdlutils().height() - s);
		tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

		// add an Image Component
		//
		mngr_->addComponent<Image>(e, &sdlutils().images().at("star"));

		// add a StarMotion component to resize/rotate the star
		//
		auto motion = mngr_->addComponent<StarMotion>(e);

		motion->rot_ = rand.nextInt(5, 10);
		motion->sizeLimit_ = rand.nextInt(2, 10);
		motion->updateFreq_ = rand.nextInt(20, 100);

		auto pts = mngr_->addComponent<Points>(e);
		pts->points_ = rand.nextInt(1, 5);
		currNumOfStars_++;
	}
}

void StarsSystem::onStarEaten(ecs::entity_t e) {

	auto point = mngr_->getComponent<Points>(e)->points_;
	mngr_->getSystem<GameCtrlSystem>()->incrScore(point);
	mngr_->setAlive(e, false);
	currNumOfStars_--;


	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

