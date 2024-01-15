#pragma once
#include "GameState.h"
#include "texture.h"

constexpr int POS_TITLE_FIN_X(300), POS_TITLE_FIN_Y(100),
				POS_VOLVER_X(250), POS_VOLVER_Y(250),
				POS_SALIR_ENX(350), POS_SALIR_ENY(400);

class EndState : public GameState
{
private:
	// --- Win / GameOver ---
	SDL_Rect rect;
	Texture* tex;

	// --- Botones ---
	Button* volverMenu;
	Button* salir;

public:
	EndState(SDLApplication* _sdlApp, bool win);
	void update() override;
	void render() const override;
	void save(std::ostream& fil) const override {}
	void handleEvent(const SDL_Event& event) override { GameState::handleEvent(event); }

	bool onEnter() override;
	bool onExit() override;
	std::string getStateID() const override { return "MenuST"; }
};

