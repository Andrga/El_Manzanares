// This file is part of the course TPV2@UCM - Samir Genaim

#include "EmptyRectangleRenderer.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

EmptyRectangleRenderer::EmptyRectangleRenderer() :
		EmptyRectangleRenderer(build_sdlcolor(0xffffffff)) {
}

EmptyRectangleRenderer::EmptyRectangleRenderer(SDL_Color color) :
		color_(color) {
}

EmptyRectangleRenderer::~EmptyRectangleRenderer() {
}

void EmptyRectangleRenderer::render(Container *o) {
	auto &pos_ = o->getPos();
	auto width_ = o->getWidth();
	auto height_ = o->getHeight();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_.getX(), pos_.getY(), width_, height_);

	SDL_RenderDrawRect(sdlutils().renderer(), &rect);
}
