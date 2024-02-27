// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class PausedState: public GameState {
public:
	PausedState();
	virtual ~PausedState();
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
};

