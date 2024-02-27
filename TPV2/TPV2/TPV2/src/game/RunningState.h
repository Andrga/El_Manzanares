// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;
class AsteroidsFacade;
class FighterFacade;

class RunningState: public GameState {
public:
	RunningState(AsteroidsFacade *ast_mngr, FighterFacade *fighter_mngr);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	void checkCollisions();
	void onFigherDeath();
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	FighterFacade *fighter_mngr_;
	Uint32 lastTimeGeneratedAsteroids_;

};

