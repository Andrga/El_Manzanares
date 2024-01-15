#pragma once
#include "GameState.h"
#include "EventHandler.h"
#include "Vector2D.h"

constexpr double POS_CONTINUARX(285), POS_CONTINUARY(100),
				POS_GUARDARX(214), POS_GUARDARY(200),
				POS_CARGARX(225), POS_CARGARY(300),
				POS_SALIR_PAX(330), POS_SALIR_PAY(400);


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

