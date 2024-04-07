// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/LifeComponent.h"
#include "../components/InmuneComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
	pmTR_(nullptr), speed_(-5) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// PacMan:
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	mngr_->addComponent<LifeComponent>(pacman);
	mngr_->addComponent<InmuneComponent>(pacman);

}

void PacManSystem::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) {

			// Rota derecha
			pmTR_->rot_ += 90.0f;

			// Cambia la direccion
			//pmTR_->vel_ = Vector2D(0, speed_).rotate(pmTR_->rot_);
			pmTR_->vel_ = pmTR_->vel_.rotate(90.0f);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) {

			// Rota izquierda
			pmTR_->rot_ -= 90.0f;

			// Settea velocidad
			//pmTR_->vel_ = Vector2D(0, speed_).rotate(pmTR_->rot_);
			pmTR_->vel_ = pmTR_->vel_.rotate(-90.0f);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) {

			// Settea la velocidad a speed
			pmTR_->vel_ = Vector2D(0, speed_);

			// Settea velocidad
			pmTR_->vel_ = Vector2D(0, speed_).rotate(pmTR_->rot_);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) {

			// Settea la velocidad a 0
			pmTR_->vel_ = Vector2D(0, 0);

		}

	}

	// move the pacman
	pmTR_->pos_ = pmTR_->pos_ + pmTR_->vel_;

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

}

void PacManSystem::resetPos()
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto eTrans = mngr_->getComponent<Transform>(e);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	eTrans->pos_ = Vector2D(x, y);
}

void PacManSystem::resetLifes()
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<LifeComponent>(e)->resetLifes();
}

void PacManSystem::recieve(const Message& message)
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto eImm = mngr_->getComponent<InmuneComponent>(e);
	auto eLif = mngr_->getComponent<LifeComponent>(e);

	switch (message.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		eLif->hit();
		break;
	case  _m_IMMUNITY_END:
		eImm->setInmune(false);
		break;
	default:
		break;
	}
}
