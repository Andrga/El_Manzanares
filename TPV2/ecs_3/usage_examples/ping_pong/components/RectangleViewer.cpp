// This file is part of the course TPV2@UCM - Samir Genaim

#include "RectangleViewer.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

RectangleViewer::RectangleViewer() :
		RectangleViewer(build_sdlcolor(0xffffffff), false) {
}

RectangleViewer::RectangleViewer(SDL_Color color, bool empty) :
		tr_(nullptr), //
		empty_(empty), //
		color_(color) {
}

RectangleViewer::~RectangleViewer() {
}

void RectangleViewer::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void RectangleViewer::render() {
	auto &pos = tr_->getPos();
	auto width = tr_->getWidth();
	auto height = tr_->getHeight();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));
	SDL_Rect rect = build_sdlrect(pos.getX(), pos.getY(), width, height);

	if (empty_) {
		SDL_RenderDrawRect(sdlutils().renderer(), &rect);
	} else {
		SDL_RenderFillRect(sdlutils().renderer(), &rect);
	}
}
