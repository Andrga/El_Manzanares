#pragma once
#include "GameState.h"
class PauseState :  public GameState
{
public:
	PauseState(SDLApplication* _sdlApp) : GameState(_sdlApp) {}
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(ostream& fil) const override;

	bool onEnter() override;
	bool onExit() override;
	string getStateID() const override { return "MenuST"; }
};

