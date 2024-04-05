// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/messages.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"

CollisionsSystem::CollisionsSystem() :
		ballTr_(nullptr), active_(false) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
	ballTr_ = mngr_->getComponent<Transform>(
			mngr_->getHandler(ecs::hdlr::BALL));
	assert(ballTr_ != nullptr);
}

void CollisionsSystem::update() {
	if (!active_)
		return;

	bool hit = false;
	ecs::entity_t paddleHit;
	for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
		auto paddleTr_ = mngr_->getComponent<Transform>(e);
		if (Collisions::collides(paddleTr_->pos_, paddleTr_->width_,
				paddleTr_->height_, ballTr_->pos_, ballTr_->width_,
				ballTr_->height_)) {
			hit = true;
			paddleHit = e;
			break;
		}
	}

	if (hit) {
		Message m;
		m.id = _m_BALL_HIT_PADDLE;
		m.ball_hit_paddle.e = paddleHit;
		mngr_->send(m);

	} else if (ballTr_->pos_.getX() < 0) {
		Message m;
		m.id = _m_BALL_EXIT;
		m.ball_exit.side = GameCtrlSystem::LEFT;
		mngr_->send(m);
	} else if (ballTr_->pos_.getX() + ballTr_->width_ > sdlutils().width()) {
		Message m;
		m.id = _m_BALL_EXIT;
		m.ball_exit.side = GameCtrlSystem::RIGHT;
		mngr_->send(m);
	}
}

void CollisionsSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_ROUND_START:
		active_ = true;
		break;
	case _m_ROUND_OVER:
		active_ = false;
		break;
	default:
		break;
	}
}
