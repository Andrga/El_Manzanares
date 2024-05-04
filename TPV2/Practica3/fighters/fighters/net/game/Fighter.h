// This file is part of the course TPV2@UCM - Samir Genaim

/*
 * The content of this class is based on https://glouw.com/2018/03/11/littlewolf.html
 */

#pragma once

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <array>
#include <string>
#include <fstream>

#include "BulletsManager.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"

class Texture;
class InputHandler;

class Fighter {
public:

	// the status of a player
	enum PlayerState : uint8_t {
		NOT_USED, ALIVE, DEAD
	};

	// player information
	struct Player {
		uint8_t id;          // the id
		Vector2D vel;        // vel
		Vector2D pos;        // position;
		int width;
		int height;
		float speed;         // maximum speed
		float rot;         // rotation
		PlayerState state;   // the state
	};

	// maximum number of player
	static constexpr uint8_t max_player = 10;

	typedef std::array<Player, max_player> players_array;
	typedef players_array::iterator iterator;

	iterator begin() {
		return players_.begin();
	}

	iterator end() {
		return players_.end();
	}

	Fighter();
	virtual ~Fighter();

	// add a new player with identifier <id>
	void addPlayer(std::uint8_t id);

	// add a new player with identifier <id>
	void initPlayer(std::uint8_t id);

	// remove player with identifier <id>
	void removePlayer(std::uint8_t id);

	// remove player with identifier <id>
	void killPlayer(std::uint8_t id);


	void send_my_info();

	void update_player_state(Uint8 id, float x, float y, float w, float h,
			float rot);

	void update_player_info(Uint8 id, float x, float y, float w, float h,
			float rot, uint8_t state);

	void bringAllToLife();


	// render the walls, etc
	void render();

	// update the world, tec
	void update();

private:

	void shoot(Player &p);
	void spin(Player &p);
	void move(Player &p);


	// array of players
	std::array<Player, max_player> players_;

	// id of the current player, used since we allows switching between players
	uint8_t player_id_;

	Texture &fighter_img_;
	InputHandler &ihdrl_;
	Uint32 lastShoot_;

};

