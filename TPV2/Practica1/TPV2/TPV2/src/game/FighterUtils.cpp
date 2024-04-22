// This file is part of the course TPV2@UCM - Samir Genaim

#include "FighterUtils.h"

#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
FighterUtils::FighterUtils() {
}

FighterUtils::~FighterUtils() {
}

void FighterUtils::reset_fighter() {
	auto mngr_ = Game::instance()->getMngr();

	auto fighter = mngr_->getHandler(ecs::hdlr::FIGHTER);

	auto fighterTR = mngr_->getComponent<Transform>(fighter);
	int w = 50;
	int h = 50;
	fighterTR->init(
			Vector2D((sdlutils().width() - w) / 2,
					(sdlutils().height() - h) / 2), Vector2D(), w, h, 0.0f);

	auto fighterGun = mngr_->getComponent<Gun>(fighter);
	fighterGun->reset();

}

void FighterUtils::create_fighter() {
	auto mngr_ = Game::instance()->getMngr();

	auto fighter = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::FIGHTER, fighter);
	mngr_->addComponent<Transform>(fighter);
	mngr_->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	mngr_->addComponent<FighterCtrl>(fighter);
	mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<ShowAtOpossiteSide>(fighter);
	mngr_->addComponent<Health>(fighter);
	mngr_->addComponent<Gun>(fighter);
	reset_fighter();
	reset_lives();
}

void FighterUtils::reset_lives() {
	auto mngr_ = Game::instance()->getMngr();
	auto fighter = mngr_->getHandler(ecs::hdlr::FIGHTER);
	auto fighterH = mngr_->getComponent<Health>(fighter);
	fighterH->set_lives(3);
}

int FighterUtils::update_lives(int n) {
	auto mngr_ = Game::instance()->getMngr();
	auto fighter = mngr_->getHandler(ecs::hdlr::FIGHTER);
	auto fighterH = mngr_->getComponent<Health>(fighter);
	return fighterH->update_lives(n);
}
