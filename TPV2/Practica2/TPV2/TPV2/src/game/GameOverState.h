#pragma once
#include <SDL_rect.h>

#include "GameState.h"

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
	Texture* msg_;
	SDL_Rect dest_;
};
