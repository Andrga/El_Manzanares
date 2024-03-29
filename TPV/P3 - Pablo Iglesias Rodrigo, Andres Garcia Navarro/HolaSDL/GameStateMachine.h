#pragma once
#include <iostream>
#include <stack>

#include "GameState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <list>

using namespace std;
class GameStateMachine
{
protected:
	stack<GameState*> pilaEstados;
	list<GameState*> eliminaEstados;
public:
	GameStateMachine();

	// Metodos para manejar estados.
	void pushState(GameState* pState); // Anade estado sin eliminar el anterior.
	void replaceState(GameState* pState); // Sustituye el estado anterior por uno nuevo.
	void popState(); // Elimina el estado actual sin reemplazarlo por otro.

	// Metodos que hacen cosas.
	void update();
	void render() const;
	void handleEvent(SDL_Event& event);
};

