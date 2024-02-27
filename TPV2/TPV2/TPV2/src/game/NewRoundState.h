// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class AsteroidsFacade;
class FighterFacade;

class NewRoundState: public GameState {
public:
	NewRoundState(AsteroidsFacade *ast_mngr, FighterFacade *fighter_mngr);
	virtual ~NewRoundState();
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	FighterFacade *fighter_mngr_;
};

