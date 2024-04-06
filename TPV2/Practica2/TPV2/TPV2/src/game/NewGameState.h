// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class InputHandler;
class Game;
class Texture;
//class FighterFacade;
//class BlackHoleFacade;

class NewGameState : public GameState {
public:
	NewGameState();
	virtual ~NewGameState();
	void enter() override;
	void update() override;
	void leave() override;
private:
	InputHandler& ihdlr; // Referencia al InputHandler.
	Texture* messageTexture;
	SDL_Rect messageRect;

	//FighterFacade* fighter_mngr_;
	//BlackHoleFacade* BlackHole_mngr_;
};