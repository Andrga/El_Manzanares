#pragma once
#include "MissileUtils.h"

#include "Game.h"

#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"

#include "../components/Image.h"

#include "../components/Transform.h"

#include "../components/Follow.h"

#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"

constexpr float MISSILE_SIZE = 20;

MissileUtils::MissileUtils() :
	mngr_(Game::instance()->getMngr()),
	rand_(sdlutils().rand())
{}

MissileUtils::~MissileUtils()
{}

void MissileUtils::create_missiles() {

	int x = 0,
		y = 0;

	//------Para cambiar la posicion de aparicion aleatoriamente:
	int spawnPoint = rand_.nextInt(0, 4);
	//int spawnPoint = 2;
	std::cout << spawnPoint << std::endl;
	switch (spawnPoint)
	{
	case 0: // Arriba izquierda.
		x = 0;
		y = 0;
		break;
	case 1: // Arriba derecha.
		x = screenWidth;
		y = 0;
		break;
	case 2: // Abajo izquierda.
		x = 0;
		y = screenHeight;
		break;
	case 3: // Abajo derecha.
		x = screenWidth;
		y = screenHeight;
		break;
	default:
		break;
	}
	Vector2D pos(x, y);

	//------Mete una entidad al grupo MISSILE:
	auto ent = mngr_->addEntity(ecs::grp::MISSILES);

	//------Guardamos la nave y su posicion para que luego pueda seguirla:
	const auto fighter = mngr_->getHandler(ecs::hdlr::FIGHTER);
	Vector2D& fighterPos = mngr_->getComponent<Transform>(fighter)->getPos();

	//------Velocidad y direccion del misil:
	Vector2D direction = (fighterPos - pos).normalize(); // Direccion normalizada.
	int speed = rand_.nextInt(1, 4);  // Velocidad aleatoria entre 1 y 3 como dice el enunciado.
	//int speed = 10; // Para testing
	Vector2D velocity = direction * speed; // Vector velocidad.

	//------Mete los componente a la entidad.
	mngr_->addComponent<Transform>(ent, pos, velocity, MISSILE_SIZE, MISSILE_SIZE, Vector2D(0, -1).angle(velocity)); // Componente Transform.
	mngr_->addComponent<Image>(ent, &sdlutils().images().at("missile")); // Componente para renderizar la imagen.
	mngr_->addComponent<Follow>(ent, fighterPos); // Componente para que siga a la nave.

	std::cout << "\nMISIIIIIIIIIIIIIIIIIIL\n";
}

void MissileUtils::remove_all_missiles() {
	//------Guarda todas las entidades del grupo HOLES en holes.
	auto missiles = mngr_->getEntities(ecs::grp::MISSILES);

	//------Settea alive como false para todos los agujeros negros.
	for (auto e : missiles)
	{
		mngr_->setAlive(e, false);
	}

	//------Elimina las entidades muertas.
	mngr_->refresh();
}
