#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
private:
	Button* nuevaPartida;
	Button* cargarPartida;
	Button* salir;

public:
	MainMenuState(SDLApplication* _sdlApp);
	//~MainMenuState();
	void update() override;
	void render() const override;
	void save(std::ostream& fil) const override;
	void handleEvent(const SDL_Event& event) override;

	bool onEnter() override;
	bool onExit() override;
	std::string getStateID() const override { return "MenuST"; }
};

