// This file is part of the course TPV2@UCM - Samir Genaim

#include "Image.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

Image::Image() :
		tr_(), tex_() {
}

Image::Image(Texture *tex) :
		tr_(), tex_(tex) {
}

Image::~Image() {
}

void Image::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Image::render() {

	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
			tr_->getHeight());

	assert(tex_ != nullptr);
	tex_->render(dest, tr_->getRot());

}
