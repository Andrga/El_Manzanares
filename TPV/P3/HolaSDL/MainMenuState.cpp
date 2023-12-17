#include "MainMenuState.h"
#include "SDLApplication.h"

void MainMenuState::update() {

}
void MainMenuState::render() const {

}
void MainMenuState::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == (SDLK_s))
		{
			getGame()->playStateChange(true);
		}
	}

}
void MainMenuState::save(ostream& fil) const {

}

bool MainMenuState::onEnter() {
	cout << "Entrando MainMenu\n";
	return true;
}
bool MainMenuState::onExit() {
	cout << "Saliendo MainMenu\n";
	return true;
}