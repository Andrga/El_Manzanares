// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_pixels.h>
#include <SDL_render.h>

#include "../ecs/Component.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

struct RectangleViewer: ecs::Component {

	__CMPID_DECL__(ecs::cmp::RECTANGLEVIEWER)

	RectangleViewer() :
			RectangleViewer(build_sdlcolor(0xff0000ff), false) {
	}
	RectangleViewer(SDL_Color color, bool empty = false) :
			color_(color), empty_(empty) {
	}
	virtual ~RectangleViewer() {
	}

	inline void init(SDL_Color color, bool empty = false) {
		color_ = color;
		empty_ = empty;
	}

	void draw(SDL_Renderer *renderer, const SDL_Rect &dest) {
		SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));
		if (empty_) {
			SDL_RenderDrawRect(renderer, &dest);
		} else {
			SDL_RenderFillRect(renderer, &dest);
		}
	}

	SDL_Color color_;
	bool empty_;

};

