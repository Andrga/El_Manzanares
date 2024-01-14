#include "PauseState.h"
#include "Button.h"
#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

using namespace std;

PauseState::PauseState(SDLApplication* _sdlApp, PlayState* _playST) : GameState(_sdlApp), playST(_playST)
{
	continuarB = new Button(this, sdlApp->getTexture(CONTINUARP), Point2D<double>(285, 100));
	guardarB = new Button(this, sdlApp->getTexture(GUARDARP), Point2D<double>(214, 200));
	cargarB = new Button(this, sdlApp->getTexture(CARGARP), Point2D<double>(225, 300));
	salirB = new Button(this, sdlApp->getTexture(SALIR), Point2D<double>(330, 400));

	addObject(continuarB);
	addObject(guardarB);
	addObject(cargarB);
	addObject(salirB);

	// para que los botones puedan reaccionar a eventos
	addEventListener(continuarB);
	addEventListener(guardarB);
	addEventListener(cargarB);
	addEventListener(salirB);

	// uso de la expresion lambda
	continuarB->connectButton([this]() { continuar(); });
	guardarB->connectButton([this]() { guardarPartida(); });
	cargarB->connectButton([this]() { cargarPartida(); });
	salirB->connectButton([this]() { salir(); });
}

void PauseState::update()
{
	for (GameObject& e: objs)
	{
		e.update();
	}
}
void PauseState::handleEvent(const SDL_Event& event) 
{
	GameState::handleEvent(event); 
}

void PauseState::render() const
{
	// renderiza la imagen de fondo
	sdlApp->getTexture(FONDOP)->render();

	for (GameObject& a : objs) {
		a.render();
	}
}

bool PauseState::onEnter()
{
	cout << "Entrando PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	cout << "Saliendo PauseState\n";
	return true;
}


void PauseState::continuar()
{
	cout << "continuar" << endl;
	sdlApp->getStMachine()->popState();
}

void PauseState::guardarPartida()
{
	playST->saveGame();
}

void PauseState::cargarPartida()
{
	sdlApp->getStMachine()->popState();
	sdlApp->getStMachine()->replaceState(new PlayState(sdlApp, true));
}

void PauseState::salir()
{
	// settea el exit a true (del sdl application)
	sdlApp->setEndGame(true);
}