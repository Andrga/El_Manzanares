// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <string>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture* img, int rows, int cols
	, int firstFrame, int lastFrame) :
	image_(img),
	transform_(nullptr),
	currentRow_(0),
	currentCol_(0),
	nRows_(rows),
	nCols_(cols),
	firstFrame(firstFrame),
	lastFrame(lastFrame),
	currentFrame(firstFrame)
{
	frameWidth_ = image_->width() / nRows_;
	frameHeight_ = image_->height() / nCols_;
	frameTimer = sdlutils().currRealTime();
}

ImageWithFrames::~ImageWithFrames()
{
}

void ImageWithFrames::initComponent()
{
	transform_ = mngr_->getComponent<Transform>(ent_);
	assert(transform_ != nullptr);
}

void ImageWithFrames::render()
{
	if (firstFrame != lastFrame) // si la imagen no es estática
		if (frameTimer + 50
			< sdlutils().virtualTimer().currTime())
		{
			frameTimer = sdlutils().virtualTimer().currTime();
			currentFrame++;
			if (currentFrame > lastFrame) {
				currentFrame = firstFrame;
			}
		}

	SDL_Rect src = build_sdlrect(
		currentFrame % nCols_ * frameWidth_,
		currentFrame / nCols_ * frameHeight_,
		frameWidth_, frameHeight_
	);
	SDL_Rect dst = build_sdlrect(
		transform_->pos_,
		transform_->width_,
		transform_->height_);
	image_->render(src, dst, transform_->rot_);
}