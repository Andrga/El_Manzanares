// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

class Fighter;
class Bullets;
class Networking;

class Game: public Singleton<Game> {
	friend Singleton<Game> ;
	Game();
public:
	virtual ~Game();
	bool init(char *host, Uint16 port);
	void start();

	Fighter& get_fighters() {
		return *fighters_;
	}

	Bullets& get_bullets() {
		return *bm_;
	}

	Networking& get_networking() {
		return *net_;
	}



private:

	void check_collisions();


	Bullets *bm_;
	Fighter *fighters_;
	Networking *net_;

};

