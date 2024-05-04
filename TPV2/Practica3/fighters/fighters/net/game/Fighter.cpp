// This file is part of the course TPV2@UCM - Samir Genaim

#include "Fighter.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "Bullets.h"
#include "Game.h"
#include "Networking.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"


Fighter::Fighter() :
		player_id_(0), //
		fighter_img_(sdlutils().images().at("fighter")), //
		ihdrl_(ih()), //
		lastShoot_(0) {
	for (auto i = 0u; i < players_.size(); i++)
		players_[i].state = NOT_USED;
}

Fighter::~Fighter() {
}

void Fighter::addPlayer(std::uint8_t id) {
	initPlayer(id);
	player_id_ = id;
	send_my_info();
}

void Fighter::initPlayer(std::uint8_t id) {
	assert(id < players_.size() && players_[id].state == NOT_USED);

	auto &rand = sdlutils().rand();

	int x = rand.nextInt(0, sdlutils().width() - 40);
	int y = rand.nextInt(0, sdlutils().height() - 40);

	players_[id] =
			{ id, Vector2D(), Vector2D(x, y), 40, 40, 2.0f, 0.0f, ALIVE };



}

void Fighter::update() {

	Player &p = players_[player_id_];

	// dead player don't move/spin/shoot
	if (p.state != ALIVE)
		return;

	spin(p);  // handle spinning
	move(p);  // handle moving
	shoot(p); // handle shooting

	// move
	p.pos = p.pos + p.vel;

	// deaccelerate
	p.vel = p.vel * 0.995f;
	if (p.vel.magnitude() < 0.05f)
		p.vel.set(0.0f, 0.0f);

	// show at opposite side
	if (p.pos.getY() + p.height < 0.0f) {
		p.pos.setY(sdlutils().height() - 1);
	} else if (p.pos.getY() > sdlutils().height()) {
		p.pos.setY(-p.height + 1);
	}

	if (p.pos.getX() + p.width < 0.0f) {
		p.pos.setX(sdlutils().width() - 1);
	} else if (p.pos.getX() > sdlutils().width()) {
		p.pos.setX(-p.width + 1);
	}


	Game::instance()->get_networking().send_state(p.pos, p.width, p.height,
			p.rot);


}

void Fighter::render() {

	for (auto i = 0u; i < players_.size(); i++) {
		Player &p = players_[i];
		if (p.state == ALIVE) {
			SDL_Rect dest = build_sdlrect(p.pos, p.width, p.height);
			fighter_img_.render(dest, p.rot);
		}
	}

	std::string msg = std::to_string(player_id_) + " :"
			+ std::to_string(Game::instance()->get_networking().client_id());
	Texture t(sdlutils().renderer(), msg, sdlutils().fonts().at("ARIAL24"),
			build_sdlcolor(0xffffffff));

	SDL_Rect dest = { 10, 10, 20, 20 };
	t.render(dest);

}

void Fighter::move(Player &p) {
	if (ihdrl_.isKeyDown(SDL_SCANCODE_W)) {

		p.vel = p.vel + Vector2D(0, -1).rotate(p.rot) * 0.1f;
		if (p.vel.magnitude() > p.speed)
			p.vel = p.vel.normalize() * p.speed;
	}
}

void Fighter::spin(Player &p) {
	if (ihdrl_.isKeyDown(SDL_SCANCODE_L)) {
		p.rot += 5.0f;
	} else if (ihdrl_.isKeyDown(SDL_SCANCODE_H)) {
		p.rot -= 5.0f;
	}
}

void Fighter::shoot(Player &p) {
	if (ihdrl_.keyDownEvent() && ihdrl_.isKeyDown(SDL_SCANCODE_SPACE)) {
		if (sdlutils().virtualTimer().currTime() < lastShoot_ + 250)
			return;

		lastShoot_ = sdlutils().virtualTimer().currTime();

		auto c = p.pos + Vector2D(p.width / 2.0f, p.height / 2.0f);

		int bwidth = 5;
		int bheight = 20;

		Vector2D bp = c
				- Vector2D(0.0f, p.height / 2.0f + bheight / 2 + 10).rotate(
						p.rot)
				- Vector2D(bwidth / 2, bheight / 2);

		Vector2D bv = Vector2D(0, -1).rotate(p.rot)
				* (p.vel.magnitude() + 5.0f);


		Game::instance()->get_networking().send_shoot(bp, bv, bwidth, bheight,
				Vector2D(0, -1).angle(bv));

	}
}

void Fighter::removePlayer(std::uint8_t id) {
	players_[id].state = Fighter::NOT_USED;
}

void Fighter::update_player_state(Uint8 id, float x, float y, float w, float h,
		float rot) {

	Player &p = players_[id];

	p.pos.set(x, y);
	p.id = id;
	p.width = w;
	p.height = h;
	p.rot = rot;

}

void Fighter::killPlayer(std::uint8_t id) {
	players_[id].state = Fighter::DEAD;
}

void Fighter::update_player_info(Uint8 id, float x, float y, float w, float h,
		float rot, uint8_t state) {
	Player &p = players_[id];

	p.pos.set(x, y);
	p.id = id;
	p.width = w;
	p.height = h;
	p.rot = rot;
	p.state = static_cast<PlayerState>(state);
}

void Fighter::send_my_info() {
	Player &p = players_[player_id_];

	Game::instance()->get_networking().send_my_info(p.pos, p.width, p.height,
			p.rot, p.state);
}

void Fighter::bringAllToLife() {
	for (auto i = 0u; i < players_.size(); i++) {
		Player &p = players_[i];
		if (p.state == DEAD) {
			p.state = ALIVE;
			p.vel.set(0.0f, 0.f);
		}
	}
}
