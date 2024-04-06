// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/LifeComponent.h"
#include "../components/ImageWithFrames.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawGhosts();
	drawPacMan();
	drawLifes();
	drawFruits();
}

void RenderSystem::drawGhosts() {
	for (auto e : mngr_->getEntities(ecs::grp::GHOSTS)) {

		auto tr = mngr_->getComponent<Transform>(e);
		auto tex = mngr_->getComponent<Image>(e)->tex_;
		draw(tr, tex);
	}
}

void RenderSystem::drawPacMan() {
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto tr = mngr_->getComponent<Transform>(e);
	auto tex = mngr_->getComponent<Image>(e)->tex_;
	draw(tr, tex);

}

void RenderSystem::drawLifes()
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<LifeComponent>(e)->render();
}

void RenderSystem::drawFruits()
{
	for (auto e : mngr_->getEntities(ecs::grp::FRUITS)) {

		drawImageWithFrames(mngr_->getComponent<ImageWithFrames>(e));
	}
}

void RenderSystem::draw(Transform* tr, Texture* tex) {
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	assert(tex != nullptr);
	tex->render(dest, tr->rot_);
}

void RenderSystem::drawImageWithFrames(ImageWithFrames* image)
{
	if (image->firstFrame != image->lastFrame) // si la imagen no es estática
		if (image->frameTimer + 50
			< sdlutils().virtualTimer().currTime())
		{
			image->frameTimer = sdlutils().virtualTimer().currTime();
			image->currentFrame++;
			if (image->currentFrame > image->lastFrame) {
				image->currentFrame = image->firstFrame;
			}
		}

	SDL_Rect src = build_sdlrect(
		image->currentFrame % image->nCols_ * image->frameWidth_,
		image->currentFrame / image->nCols_ * image->frameHeight_,
		image->frameWidth_, image->frameHeight_
	);
	SDL_Rect dst = build_sdlrect(
		image->transform_->pos_,
		image->transform_->width_,
		image->transform_->height_);
	image->image_->render(src, dst, image->transform_->rot_);
}