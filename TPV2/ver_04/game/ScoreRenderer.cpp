// This file is part of the course TPV2@UCM - Samir Genaim

#include "ScoreRenderer.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameManager.h"

ScoreRenderer::ScoreRenderer() {
}

ScoreRenderer::~ScoreRenderer() {
}

void ScoreRenderer::render(Container *o) {
	auto gm = static_cast<GameManager*>(o);

	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(gm->getScore(0)) + " - "
					+ std::to_string(gm->getScore(1)),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
}
