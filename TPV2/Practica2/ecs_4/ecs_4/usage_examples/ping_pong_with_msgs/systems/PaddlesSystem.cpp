// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddlesSystem.h"

#include "../components/PaddleCtrl.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PaddlesSystem::PaddlesSystem() :
		ballTr_(nullptr) {
}

PaddlesSystem::~PaddlesSystem() {
}

void PaddlesSystem::initSystem() {
	auto ballEntity = mngr_->getHandler(ecs::hdlr::BALL);
	ballTr_ = mngr_->getComponent<Transform>(ballEntity);
	assert(ballTr_ != nullptr);

	// create the left paddle
	auto leftPaddle = mngr_->addEntity(ecs::grp::PADDLES);

	auto leftPaddleTr = mngr_->addComponent<Transform>(leftPaddle);
	auto leftPaddleWidth = 10.0f;
	auto leftPaddleHeight = 50.0f;
	auto leftPaddleX = 5.f;
	auto leftPaddleY = (sdlutils().height() - leftPaddleHeight) / 2.0f;
	leftPaddleTr->init(Vector2D(leftPaddleX, leftPaddleY), Vector2D(),
			leftPaddleWidth, leftPaddleHeight, 0.0f);

	mngr_->addComponent<RectangleViewer>(leftPaddle,
			build_sdlcolor(0xff0000ff));
	auto leftPaddleCtrl = mngr_->addComponent<PaddleCtrl>(leftPaddle);
//	leftPaddleCtrl->setType(PaddleCtrl::MOUSE);
	leftPaddleCtrl->setType(PaddleCtrl::AI);

	// create the right paddle
	auto rightPaddle = mngr_->addEntity(ecs::grp::PADDLES);

	auto rightPaddleTr = mngr_->addComponent<Transform>(rightPaddle);
	auto rightPaddleWidth = 10.0f;
	auto rightPaddleHeight = 50.0f;
	auto rightPaddleX = sdlutils().width() - rightPaddleWidth - 5.0f;
	auto rightPaddleY = (sdlutils().height() - rightPaddleHeight) / 2.0f;
	rightPaddleTr->init(Vector2D(rightPaddleX, rightPaddleY), Vector2D(),
			rightPaddleWidth, rightPaddleHeight, 0.0f);

	mngr_->addComponent<RectangleViewer>(rightPaddle,
			build_sdlcolor(0x00ff00ff));
	auto rightaddleCtrl = mngr_->addComponent<PaddleCtrl>(rightPaddle);
	rightaddleCtrl->setType(PaddleCtrl::MOUSE);
//	rightaddleCtrl->setType(PaddleCtrl::AI);

}

void PaddlesSystem::update() {
	for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
		movePaddle(e);
	}
}

void PaddlesSystem::movePaddle(ecs::entity_t paddle) {
	auto paddleCtrl = mngr_->getComponent<PaddleCtrl>(paddle);
	auto paddleTr = mngr_->getComponent<Transform>(paddle);

	switch (paddleCtrl->ctrlType_) {
	case PaddleCtrl::KEYBOARD:
		moveWithKeyboard(paddleCtrl, paddleTr);
		break;
	case PaddleCtrl::MOUSE:
		moveWithMouse(paddleCtrl, paddleTr);
		break;
	case PaddleCtrl::AI:
		moveWithAI(paddleCtrl, paddleTr);
		break;
	default:
		break;
	}

	paddleTr->move();

	// check collision with upper/lower borders
	if (paddleTr->pos_.getY() < 0) {
		paddleTr->pos_.setY(0.0f);
		paddleTr->vel_.set(0.0f, 0.0f);
	} else if (paddleTr->pos_.getY() + paddleTr->height_
			> sdlutils().height()) {
		paddleTr->pos_.setY(sdlutils().height() - paddleTr->height_);
		paddleTr->vel_.set(0.0f, 0.0f);
	}

}

void PaddlesSystem::moveWithKeyboard(PaddleCtrl *paddleCtrl,
		Transform *paddleTr) {
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(paddleCtrl->up_)) {
			paddleTr->vel_.setY(-paddleCtrl->speed_);
		} else if (ihdlr.isKeyDown(paddleCtrl->down_)) {
			paddleTr->vel_.setY(paddleCtrl->speed_);
		} else if (ihdlr.isKeyDown(paddleCtrl->stop_)) {
			paddleTr->vel_.setY(0.0f);
		}
	}
}

void PaddlesSystem::moveWithMouse(PaddleCtrl *paddleCtrl, Transform *paddleTr) {
	auto &ihdlr = ih();

	if (ihdlr.mouseMotionEvent()) {
		paddleTr->pos_.setY(ihdlr.getMousePos().second);
	}
}

void PaddlesSystem::moveWithAI(PaddleCtrl *paddleCtrl, Transform *paddleTr) {
	if (ballComingTowardsPaddle(paddleTr->pos_)) {
		float diff = (ballTr_->pos_.getY() + ballTr_->height_ / 2.0f)
				- (paddleTr->pos_.getY() + paddleTr->height_ / 2.0f);
		if (abs(diff) < 10) {
			paddleTr->vel_.setY(0.0f);
		} else {
			paddleTr->vel_.setY(
					(diff > 0.0f ? 1.0f : -1.0f) * 1.0f
							* ballTr_->vel_.magnitude());
		}
	} else {
		float diff = (sdlutils().height() / 2.0f)
				- (paddleTr->pos_.getY() + paddleTr->height_ / 2.0f);
		if (abs(diff) < 10) {
			paddleTr->vel_.setY(0.0);
		} else {
			paddleTr->vel_.setY((diff > 0 ? 1 : -1) * 5.0f);
		}
	}
}

bool PaddlesSystem::ballComingTowardsPaddle(const Vector2D &pos) {
	return (pos.getX() < ballTr_->pos_.getX() && ballTr_->vel_.getX() < 0)
			|| (pos.getX() > ballTr_->pos_.getX() && ballTr_->vel_.getX() > 0);
}

