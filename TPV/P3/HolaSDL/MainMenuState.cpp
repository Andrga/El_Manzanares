#include "MainMenuState.h"

void MainMenuState::update() {

}
void MainMenuState::render() const {

}
void MainMenuState::handleEvent(const SDL_Event& event) {

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