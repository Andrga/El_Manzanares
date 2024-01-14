#pragma once
#include "GameState.h"
#include "EventHandler.h"

class PauseState : public GameState
{
private:
	Button* continuarB;
	Button* guardarB;
	Button* cargarB;
	Button* salirB;

	PlayState* playST;

	// funciones de los botones
	void continuar();
	void guardarPartida();
	void cargarPartida();
	void salir();

public:
	PauseState(SDLApplication* _sdlApp, PlayState* _playST);
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& fil) const override {}
	std::string getStateID() const override { return"PauseST"; }

	bool onEnter() override;
	bool onExit() override;
};

