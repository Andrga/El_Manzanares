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
	if (sdlutils().currRealTime() > frameTimer + 10)
	{
		currentCol_ = (currentCol_ + 1) % (nCols_ - 1);
		currentRow_ = (currentRow_ + 1) % (nRows_ - 1);
		frameTimer = sdlutils().currRealTime();
		currentFrame = currentRow_ * nCols_ + currentCol_;
	}

	auto frame = Vector2D(currentCol_ * frameWidth_, currentRow_ * frameHeight_);
	const SDL_Rect srce = build_sdlrect(
		frame,
		frameWidth_,
		frameHeight_
	);
	const SDL_Rect dest = build_sdlrect(
		transform_->pos_,
		transform_->width_,
		transform_->height_
	);
	image_->render(srce, dest, transform_->rot_);
}