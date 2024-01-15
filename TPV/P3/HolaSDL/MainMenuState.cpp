#include "MainMenuState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include "Button.h"
#include "checkML.h"

using namespace std;

MainMenuState::MainMenuState(SDLApplication* _sdlApp)
	: GameState(_sdlApp)
{
	nuevaPartida = new Button(this, sdlApp->getTexture(NUEVAP), Point2D<double>(POS_NUEVA_PARTIDAX, POS_NUEVA_PARTIDAY));
	cargarPartida = new Button(this, sdlApp->getTexture(CARGARP), Point2D<double>(POS_CARGAR_PARTIDAX, POS_CARGAR_PARTIDAY));
	salir = new Button(this, sdlApp->getTexture(SALIR), Point2D<double>(POS_SALIR_MPRX, POS_SALIR_MPRY));

	addObject(nuevaPartida);
	addObject(cargarPartida);
	addObject(salir);

	addEventListener(nuevaPartida);
	addEventListener(cargarPartida);
	addEventListener(salir);

	nuevaPartida->connectButton([this]() {sdlApp->getStMachine()->replaceState(new PlayState(sdlApp, false)); });
	cargarPartida->connectButton([this]() {sdlApp->getStMachine()->replaceState(new PlayState(sdlApp, true)); });
	salir->connectButton([this]() {sdlApp->setEndGame(true); });
}

/*
MainMenuState::~MainMenuState() {
	delete nuevaPartida;
	//delete cargarPartida;
	//delete salir;
}*/

void MainMenuState::update() {
	for (GameObject& e : objs)
	{
		e.update();
	}
}
void MainMenuState::render() const {
	sdlApp->getTexture(MENUFONDO)->render();

	for (GameObject& e : objs)
	{
		e.render();
	}
}
void MainMenuState::handleEvent(const SDL_Event& event) {

	GameState::handleEvent(event);
	/*for (EventHandler* e : listeners)
	{
		e->handleEvent(event);
	}*/
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