// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;

class CollisionsSystem;
class GameCtrlSystem;
class GhostSystem;
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
	RunningState(/*CollisionsSystem* cs, GameCtrlSystem* gcs, GhostSystem* gs, PacManSystem* ps, RenderSystem* rs, StarsSystem* ss*/);
	virtual ~RunningState();
	void enter() override;
	void update() override;
	void leave() override;

private:
	CollisionsSystem* collisionsSystem;
	GameCtrlSystem* gameCtrlSystem;
	GhostSystem* ghostSystem;
	PacManSystem* pacManSystem;
	RenderSystem* renderSystem;
	StarsSystem* starsSystem;
};