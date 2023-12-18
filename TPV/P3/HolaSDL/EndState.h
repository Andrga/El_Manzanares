#pragma once
#include "GameState.h"
#include "texture.h"
class EndState : public GameState
{
private:
	// --- Win / GameOver ---
	SDL_Rect* rect;
	Texture* tex;

	// --- Botones ---
	Button* volverMenu;
	Button* salir;

public:
	EndState(SDLApplication* _sdlApp, bool win);
	void update() override;
	void render() const override;
	void save(ostream& fil) const override {}
	void handleEvent(const SDL_Event& event) override { GameState::handleEvent(event); }

	bool onEnter() override;
	bool onExit() override;
	string getStateID() const override { return "MenuST"; }
};

