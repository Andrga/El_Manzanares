// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class NewRoundState : public GameState {
public:
	NewRoundState();

	virtual ~NewRoundState();
	void enter() override;
	void update() override;
	void leave() override;

private:
	Texture* messageTexture;
	SDL_Rect messageRect;
};