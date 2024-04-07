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
		mngr_->getComponent<ImageWithFrames>(e)->render();
	}
}

void RenderSystem::drawPacMan() {
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<ImageWithFrames>(e)->render();

}

void RenderSystem::drawLifes()
{
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->getComponent<LifeComponent>(e)->render();
}

void RenderSystem::drawFruits()
{
	for (auto e : mngr_->getEntities(ecs::grp::FRUITS)) {
		mngr_->getComponent<ImageWithFrames>(e)->render();
	}
}

void RenderSystem::drawMsgs() {
	// draw the score
	//
	auto score = mngr_->getSystem<GameCtrlSystem>()->getScore();

	Texture scoreTex(sdlutils().renderer(), std::to_string(score),
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
		(sdlutils().width() - scoreTex.width()) / 2.0f, //
		10.0f, //
		scoreTex.width(), //
		scoreTex.height());

	scoreTex.render(dest);

	// draw add stars message
	sdlutils().msgs().at("addstars").render(10, 10);

}

void RenderSystem::draw(Transform* tr, Texture* tex) {
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	assert(tex != nullptr);
	tex->render(dest, tr->rot_);
}