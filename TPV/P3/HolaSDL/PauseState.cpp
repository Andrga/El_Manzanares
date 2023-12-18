#include "PauseState.h"
#include "Button.h"
#include "PlayState.h"
#include "checkML.h"
#include "SDLApplication.h"

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
void PauseState::save(ostream& fil) const {

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
	cout << "Inserte num de ranura de guardado: " << endl;
	playST->saveGame();
}

void PauseState::cargarPartida()
{
	cout << "Inserte num de ranura de carga: " << endl;
	/*
	char k;
	string file;

	// lee el numero
	cin >> k;

	// crea un string con el archivo
	file = "..\\saved\\save" + to_string(k - '0');

	// crea un nuevo estado con la direccion indicada
	GameState* ps = new PlayState(app, file);

	app;

	app->getgsMachine();

	// crea un nuevo play state y lo remplaza con el anterior
	app->getgsMachine()->replaceState(ps);

	// quita este estado
	app->getgsMachine()->popState();*/
}

void PauseState::salir()
{
	// settea el exit a true (del sdl application)
	sdlApp->setEndGame(true);
}