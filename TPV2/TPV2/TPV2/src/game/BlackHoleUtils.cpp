#pragma once
#include "BlackHoleUtils.h"
#include "Game.h"
#include "ImageRenderer.h"
#include "RotateComponent.h"
#include "../components/Transform.h"

#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"

BlackHoleUtils::BlackHoleUtils() :
	mngr_(Game::instance()->getMngr()),
	rand_(sdlutils().rand())
{

}

BlackHoleUtils::~BlackHoleUtils(){}

void BlackHoleUtils::create_blackholes(int n) {
	const Vector2D center(
		sdlutils().width() / 2,
		sdlutils().height() / 2
	);
	const double alpha = 360 / n;


	// Crea n agujeros negros
	for (int i = 0; i < n; i++)
	{
		int radio = rand_.nextInt(RAD_MIN, 300);
		
		// Calcula la posicion exacta del agujero negro
		Vector2D pos(
			center.getX() + radio * cos(alpha * i),
			center.getY() + radio * sin(alpha * i)
		);

		//
		auto ent = mngr_->addEntity(ecs::grp::HOLES);
		mngr_->addComponent<Trans
	}
}