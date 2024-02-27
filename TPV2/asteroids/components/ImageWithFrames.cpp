// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <string>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture *tex, int rows, int cols, int x, int y,
		int w, int h, int srow, int scol, int nrow, int ncol) :
		tex_(tex), //
		tr_(nullptr), //
		currFrameR_(0), //
		currFrameC_(0), //
		x_(x), //
		y_(y), //
		w_(w), //
		h_(h), //
		srow_(srow), //
		scol_(scol), //
		nrow_(nrow), //
		ncol_(ncol), //
		lastFrameChange_(0)
{
	frameWidth_ = tex_->width() / cols;
	frameHeight_ = tex->height() / rows;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ImageWithFrames::render() {
	if (sdlutils().virtualTimer().currTime() > lastFrameChange_ + 50) {
		lastFrameChange_ = sdlutils().virtualTimer().currTime();
		currFrameC_ = (currFrameC_ + 1) % ncol_;
		if (currFrameC_ == 0)
			currFrameR_ = (currFrameR_ + 1) % nrow_;
	}

	int r = (currFrameR_ + srow_);
	int c = (currFrameC_ + scol_);
	auto src = build_sdlrect(c * frameWidth_ + x_, r * frameHeight_ + y_, w_,
			h_);

	auto dest = build_sdlrect(tr_->getPos(), tr_->getWidth(), tr_->getHeight());

	tex_->render(src, dest, tr_->getRot());

}
