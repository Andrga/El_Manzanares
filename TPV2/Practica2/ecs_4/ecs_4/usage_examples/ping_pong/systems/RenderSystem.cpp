// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/Image.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
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
	drawMsgs();
	drawScore();
	drawBall();
	drawPaddles();
}

void RenderSystem::drawMsgs() {
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();

	// message when game is not running
	if (state != GameCtrlSystem::RUNNING) {

		// game over message
		if (state == GameCtrlSystem::GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state == GameCtrlSystem::NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}
}

void RenderSystem::drawScore() {

	auto leftScore = mngr_->getSystem<GameCtrlSystem>()->getScore(0);
	auto rightScore = mngr_->getSystem<GameCtrlSystem>()->getScore(1);

	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(leftScore) + " - " + std::to_string(rightScore),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}

void RenderSystem::drawBall() {
	auto ball = mngr_->getHandler(ecs::hdlr::BALL);
	auto ballTr = mngr_->getComponent<Transform>(ball);
	auto ballImg = mngr_->getComponent<Image>(ball);

	SDL_Rect dest = build_sdlrect(ballTr->pos_, ballTr->width_,
			ballTr->height_);

	assert(ballImg->tex_ != nullptr);
	ballImg->tex_->render(dest, ballTr->rot_);

}

void RenderSystem::drawPaddles() {
	for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
		auto paddleTr_ = mngr_->getComponent<Transform>(e);

		SDL_Rect dest = build_sdlrect(paddleTr_->pos_.getX(),
				paddleTr_->pos_.getY(), paddleTr_->width_, paddleTr_->height_);

		mngr_->getComponent<RectangleViewer>(e)->draw(sdlutils().renderer(),
				dest);
	}
}
