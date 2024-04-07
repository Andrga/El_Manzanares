// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;

class CollisionsSystem;
class FoodSystem;
class GameCtrlSystem;
class GhostSystem;
class ImmunitySystem;
class PacManSystem;
class RenderSystem;
class StarsSystem;

//class StarsSystem;
//class AsteroidsFacade;
//class FighterFacade;
//class BlackHoleFacade;
//class MissileFacade;

class RunningState : public GameState {
public:
	RunningState();
	virtual ~RunningState();
	void enter() override;
	void update() override;
	void leave() override;

private:
	CollisionsSystem* collisionsSystem;
	FoodSystem* foodSystem;
	GameCtrlSystem* gameCtrlSystem;
	GhostSystem* ghostSystem;
	ImmunitySystem* immunitySystem;
	PacManSystem* pacManSystem;
	RenderSystem* renderSystem;
	StarsSystem* starsSystem;
};