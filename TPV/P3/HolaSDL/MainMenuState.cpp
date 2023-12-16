#include "MainMenuState.h"

void MainMenuState::update() {

}
void MainMenuState::render() const {

}

bool MainMenuState::onEnter() {
	cout << "Entrando MainMenu\n";
	return true;
}
bool MainMenuState::onExit() {
	cout << "Saliendo MainMenu\n";
	return true;
}