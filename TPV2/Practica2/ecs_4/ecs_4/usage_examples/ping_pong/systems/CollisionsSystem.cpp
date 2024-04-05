// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"
CollisionsSystem::CollisionsSystem() :
		ballTr_(nullptr) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
	ballTr_ = mngr_->getComponent<Transform>(
			mngr_->getHandler(ecs::hdlr::BALL));
	assert(ballTr_ != nullptr);
}

void CollisionsSystem::update() {

	auto gameCtrlSystem = mngr_->getSystem<GameCtrlSystem>();

	if (gameCtrlSystem->getState() != GameCtrlSystem::RUNNING)
		return;

	bool ballCollidesWithPaddle = false;

	for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
		auto paddleTr_ = mngr_->getComponent<Transform>(e);
		ballCollidesWithPaddle = Collisions::collides(paddleTr_->pos_,
				paddleTr_->width_, paddleTr_->height_, ballTr_->pos_,
				ballTr_->width_, ballTr_->height_);

		if (ballCollidesWithPaddle)
			break;
	}

	if (ballCollidesWithPaddle) {

		// change the direction of the ball, and increment the speed
		auto &vel = ballTr_->vel_; // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ballTr_->pos_.getX() < 0)
		gameCtrlSystem->onBallExit(GameCtrlSystem::LEFT);
	else if (ballTr_->pos_.getX() + ballTr_->width_ > sdlutils().width())
		gameCtrlSystem->onBallExit(GameCtrlSystem::RIGHT);

}
