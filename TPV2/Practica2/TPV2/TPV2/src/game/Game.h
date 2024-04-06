// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"
#include "../ecs/ecs.h"
#include "GameState.h"
#include <vector>

class Game : public Singleton<Game> {
public:

	// Singleton del Game.
	friend Singleton<Game>;

	// Enum con los estados del juego.
	enum State { RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER };

	// Constructora.
	Game();
	//Destructora.
	virtual ~Game();

	void init();

	void start();

	inline ecs::Manager* getMngr() {
		return mngr_;
	}

	inline void setState(State s) {

		GameState* new_state = nullptr;
		switch (s) {
		case RUNNING:
			new_state = running_state_;
			break;
		case PAUSED:
			new_state = paused_state_;
			break;
		case NEWGAME:
			new_state = newgame_state_;
			break;
		case NEWROUND:
			new_state = newround_state_;
			break;
		case GAMEOVER:
			new_state = gameover_state_;
			break;
		default:
			break;
		}
		current_state_->leave();
		current_state_ = new_state;
		current_state_->enter();
	}

private:
	ecs::Manager* mngr_;

	ecs::System* pacmanSys_;
	ecs::System* gameCtrlSys_;
	ecs::System* startsSys_;
	ecs::System* renderSys_;
	ecs::System* collisionSys_;
	ecs::System* ghostSys_;

	// Estados de juego.
	GameState* current_state_; // Estado acutal.
	GameState* paused_state_; // Estado de pausa.
	GameState* running_state_; // Estado de juego.
	GameState* newgame_state_; // Estado de juego nuevo.
	GameState* newround_state_; // Estado de nueva ronda.
	GameState* gameover_state_; // EStado de fin de juego.
};