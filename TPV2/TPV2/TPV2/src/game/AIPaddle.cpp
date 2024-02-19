// This file is part of the course TPV2@UCM - Samir Genaim

#include "AIPaddle.h"

#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "Container.h"

AIPaddle::AIPaddle(GameObject *ball) :
		ball_(ball) {
}

AIPaddle::~AIPaddle() {

}

void AIPaddle::handleInput(Container *o) {

	auto &vel = o->getVel();
	auto &pos = o->getPos();
	auto height = o->getHeight();

	if (ballComingTowardsPaddle(pos)) {
		float diff = (ball_->getPos().getY() + ball_->getHeight() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0f);
		} else {
			vel.setY(
					(diff > 0.0f ? 1.0f : -1.0f) * 1.0f
							* ball_->getVel().magnitude());
		}
	} else {
		float diff = (sdlutils().height() / 2.0f)
				- (pos.getY() + height / 2.0f);
		if (abs(diff) < 10) {
			vel.setY(0.0);
		} else {
			vel.setY((diff > 0 ? 1 : -1) * 5.0f);
		}
	}
}


bool AIPaddle::ballComingTowardsPaddle(const Vector2D &pos) {

	return (pos.getX() < ball_->getPos().getX()
			&& ball_->getVel().getX() < 0)
			|| (pos.getX() > ball_->getPos().getX()
					&& ball_->getVel().getX() > 0);
}
