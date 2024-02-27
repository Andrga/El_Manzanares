// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class GameOverState: public GameState {
public:
	GameOverState();
	virtual ~GameOverState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	Texture *msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
};

