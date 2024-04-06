// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class InputHandler;
class Game;
//class FighterFacade;
//class BlackHoleFacade;

class NewGameState : public GameState {
public:
	NewGameState(Game& game_);
	virtual ~NewGameState();
	void enter() override;
	void update() override;
	void leave() override;
private:
	SDL_Rect dest_;
	InputHandler& ihdlr; // Referencia al InputHandler.
	Game& game; // Referencia al Game.
	//FighterFacade* fighter_mngr_;
	//BlackHoleFacade* BlackHole_mngr_;
};