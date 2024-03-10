#pragma once
#include "BlackHoleUtils.h"

#include "Game.h"

#include "../components/Image.h"

#include "../components/Transform.h"

#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"

//#include "RotateComponent.h"

constexpr float HOLE_SIZE = 50;

BlackHoleUtils::BlackHoleUtils() :
	mngr_(Game::instance()->getMngr()),
	rand_(sdlutils().rand())
{

}

BlackHoleUtils::~BlackHoleUtils() {}

void BlackHoleUtils::create_blackholes(int n) {
	const Vector2D center(
		sdlutils().width() / 2,
		sdlutils().height() / 2
	);
	const double alpha = 360 / n;


	// Crea n agujeros negros.
	for (int i = 0; i < n; i++)
	{
		int radio = rand_.nextInt(RAD_MIN, 300);

		// Calcula la posicion exacta del agujero negro.
		Vector2D pos(
			center.getX() + radio * cos(alpha * i),
			center.getY() + radio * sin(alpha * i)
		);

		// Crea una entidad y le anade los componentes necesarios.
		auto ent = mngr_->addEntity(ecs::grp::HOLES);
		mngr_->addComponent<Transform>(ent,
			pos,
			Vector2D(0, 0),
			HOLE_SIZE,
			HOLE_SIZE,
			0.0f
		);
		mngr_->addComponent<Image>(ent, &sdlutils().images().at("black-hole"));
	}
}
void BlackHoleUtils::remove_all_blackholes() {
	// Guarda todas las entidades del grupo HOLES en holes.
	auto holes = mngr_->getEntities(ecs::grp::HOLES);

	// Settea alive como false para todos los agujeros negros.
	for (auto e : holes)
	{
		mngr_->setAlive(e, false);
	}

	// Elimina las entidades muertas.
	mngr_->refresh();
}