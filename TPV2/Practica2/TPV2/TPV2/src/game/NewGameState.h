// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

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
	Texture* messageTexture_;
	SDL_Rect messageRect_;

	//FighterFacade* fighter_mngr_;
	//BlackHoleFacade* BlackHole_mngr_;
};