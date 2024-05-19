// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_NEW_GAME, // Mensaje que se manda al iniciar el juego.
	_m_ROUND_START, // Mensaje que se manda al iniciar una ronda.
	_m_ROUND_OVER, // Mensaje que se manda cuando acaba una ronda.
	_m_GAME, // No se usa.
	_m_GAME_OVER, // fin del juego
	_m_PACMAN_FOOD_COLLISION, // Colision entre el PacMan y una fruta.
	_m_PACMAN_GHOST_COLLISION, // Colision entre el PacMan y un fantasma.
	_m_IMMUNITY_START, // La inmunidad ha empezado.
	_m_IMMUNITY_END, // La inmunidad ha acabado.
	_m_WIN_GAME, // Mensaje de ganar el juego.
	_m_PAUSE_GAME, // Mensaje para pausar el juego.
	_m_UNPAUSE_GAME, // Mensaje para despausar el juego.
	_m_FRUIT_EAT, // Comer una fruta normal.
	_m_GHOST_EAT, // Comer un fantasma.

};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {		
		
		struct {
			ecs::entity_t e;
		} ent_collided;
	};
};