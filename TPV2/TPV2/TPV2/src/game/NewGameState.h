// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;
class FighterFacade;

class NewGameState: public GameState {
public:
	NewGameState(FighterFacade *fighter_mngr);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	FighterFacade *fighter_mngr_;
};

