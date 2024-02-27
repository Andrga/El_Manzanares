// This file is part of the course TPV2@UCM - Samir Genaim

#include "AsteroidsUtils.h"

#include "../components/Follow.h"
#include "../components/Generations.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/TowardsDestination.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"


AsteroidsUtils::AsteroidsUtils() :
		rand_(sdlutils().rand()), width_(sdlutils().width()), height_(
				sdlutils().height()) {
}

AsteroidsUtils::~AsteroidsUtils() {
}

void AsteroidsUtils::remove_all_asteroids() {
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::ASTEROIDS)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void AsteroidsUtils::create_asteroids(int n) {

	for (int i = 0; i < n; i++) {

		int y = 0, x = 0;
		int side = rand_.nextInt(0, 4);

		switch (side) {
		case 0:
			y = sdlutils().height() - 20;
			x = rand_.nextInt(0, width_);
			break;
		case 1:
			y = 0;
			x = rand_.nextInt(0, width_);
			break;
		case 2:
			y = rand_.nextInt(0, height_);
			x = 0;
			break;
		case 3:
			y = rand_.nextInt(0, height_);
			x = sdlutils().width() - 20;
			break;
		default:
			break;
		}

		Vector2D p = Vector2D(x, y);
		Vector2D c = Vector2D(width_ / 2 + rand_.nextInt(-100, 100),
				height_ / 2 + rand_.nextInt(-100, 100));

		Vector2D v = (c - p).normalize() * (rand_.nextInt(1, 10) / 10.0f);

		auto g = rand_.nextInt(1, 4);
		generateAsteroid(p, v, g);

	}

}

void AsteroidsUtils::generateAsteroid(const Vector2D &p, const Vector2D &v,
		int g) {

	auto mngr = Game::instance()->getMngr();

	auto a = mngr->addEntity(ecs::grp::ASTEROIDS);

	mngr->addComponent<Transform>(a, p, v, 10 + 5 * g, 10 + 5 * g, 0.0f);
	mngr->addComponent<ShowAtOpossiteSide>(a);
	mngr->addComponent<Generations>(a, g);

	mngr->addComponent<ImageWithFrames>(a, //
			&sdlutils().images().at("asteroid"), //
			5, 6, //
			0, 0, //
			85, 95, //
			0, 0, //
			5, 6);

	int move_style = rand_.nextInt(0, 5);
	switch (move_style) {
	case 0: {
		auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
		auto fighterTR = mngr->getComponent<Transform>(fighter);
		mngr->addComponent<Follow>(a, fighterTR->getPos());
		break;
	}
	case 1:
		mngr->addComponent<TowardsDestination>(a);
		break;
	default:
		break;
	}
}

void AsteroidsUtils::split_astroid(ecs::entity_t a) {
	auto mngr = Game::instance()->getMngr();
	auto tr = mngr->getComponent<Transform>(a);
	auto gn = mngr->getComponent<Generations>(a);

	auto &p = tr->getPos();
	auto &v = tr->getVel();

	int g = gn->getGenerations() - 1;

	mngr->setAlive(a, false);

	if (g > 0) {
		for (auto i = 0u; i < 2; i++) {
			int r = sdlutils().rand().nextInt(1, 360);
			auto w = tr->getWidth();
			generateAsteroid(p + v.rotate(r) * 2 * w, v.rotate(r) * 1.1f, g);
		}
	}
}
