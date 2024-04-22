// This file is part of the course TPV2@UCM - Samir Genaim

#include "Gun.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

Gun::Gun() :
		bullets_(), //
		img_(sdlutils().images().at("fire")), //
		tr_(nullptr), //
		ihdrl(ih()), //
		lastShoot_(), //
		lastUsed_(-1) {
}

Gun::~Gun() {
}

void Gun::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Gun::update() {

	if (ihdrl.keyDownEvent() && ihdrl.isKeyDown(SDL_SCANCODE_S)) {
		if (sdlutils().virtualTimer().currTime() < lastShoot_ + 250)
			return;

		lastShoot_ = sdlutils().virtualTimer().currTime();

		auto &pos = tr_->getPos();
		auto &vel = tr_->getVel();
		auto h = tr_->getHeight();
		auto w = tr_->getWidth();
		auto r = tr_->getRot();

		auto c = pos + Vector2D(w / 2.0f, h / 2.0f);

		int bwidth = 5;
		int bheight = 20;

		Vector2D bp = c - Vector2D(0.0f, h / 2.0f + bheight / 2).rotate(r)
				- Vector2D(bwidth / 2, bheight / 2);
		
		Vector2D bv = Vector2D(0, -1).rotate(r) * (vel.magnitude() + 5.0f);

		shoot(bp, bv, bwidth, bheight, Vector2D(0, -1).angle(bv));
	}

	int width = sdlutils().width();
	int height = sdlutils().height();

	for (Bullet &b : bullets_) {
		if (b.used) {
			b.pos = b.pos + b.vel;
			if (!b.pos.inRange(-b.width, width, -b.height, height)) {
				b.used = false;
			}
		}
	}

}

void Gun::render() {
	for (Bullet &b : bullets_) {
		if (b.used) {
			SDL_Rect dest = build_sdlrect(b.pos, b.width, b.height);
			img_.render(dest, b.rot);
		}
	}
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {

	int idx = (lastUsed_ + 1) % max_bullets;
	while (idx != lastUsed_ && bullets_[idx].used) {
		idx = (idx + 1) % max_bullets;
	}

	if (idx != lastUsed_) {
		lastUsed_ = idx;
		Bullet &b = bullets_[idx];
		b.used = true;
		b.pos = p;
		b.vel = v;
		b.width = width;
		b.height = height;
		b.rot = r;

		sdlutils().soundEffects().at("gunshot").play();
	}

}

void Gun::reset() {
	for (Bullet &b : bullets_) {
		b.used = false;
	}
}

