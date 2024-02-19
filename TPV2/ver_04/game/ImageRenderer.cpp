// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageRenderer.h"

#include "../sdlutils/Texture.h"
#include "Container.h"

ImageRenderer::ImageRenderer(Texture *img) :
		img_(img) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(Container *o) {
	SDL_Rect dest = build_sdlrect(o->getPos(), o->getWidth(), o->getHeight());
	img_->render(dest);
}
