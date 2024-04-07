#pragma once
#include <SDL_rect.h>

#include "GameState.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

class Texture;
class InputHandler;

class GameOverState : public GameState {
public:
	GameOverState();
	virtual ~GameOverState();
	void enter() override;
	void update() override;
	void leave() override;
private:
	Texture* messageTexture;
	SDL_Rect messageRect;

	ecs::entity_t pacMan; // Referencia al PacMan.
};
