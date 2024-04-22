// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <array>

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/Vector2D.h"

class Texture;
class Transform;
class InputHandler;

class Gun: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GUN)

	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;
	};

	constexpr static auto max_bullets = 20;
	typedef std::array<Bullet, max_bullets> bullets_array;
	typedef bullets_array::iterator iterator;

	Gun();
	virtual ~Gun();
	void initComponent() override;
	void update() override;
	void render() override;
	void reset();

	iterator begin() {
		return bullets_.begin();
	}

	iterator end() {
		return bullets_.end();
	}

private:
	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array bullets_;
	Texture &img_;
	Transform *tr_;
	InputHandler &ihdrl;
	Uint32 lastShoot_;
	int lastUsed_;

};

