// This file is part of the course TPV2@UCM - Samir Genaim

#include "Health.h"

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

Health::Health() :
		Health(0) {
}

Health::Health(int l) :
		lives_(l), img_(sdlutils().images().at("heart")) {
	assert(lives_>=0);
}

Health::~Health() {
}

void Health::initComponent() {
}

void Health::render() {
	SDL_Rect dest { 0, 5, 30, 30 };
	for (int i = 0; i < lives_; i++) {
		dest.x = 2 + i * 30;
		img_.render(dest);
	}
}
