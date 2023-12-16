#pragma once
#include <iostream>
#include <stack>

#include "GameState.h"

using namespace std;
class GameStateMachine
{
private:
	stack<GameState*> pilaEstados;
public:
	GameStateMachine();

	// Metodos para manejar estados.
	void pushState(GameState* pState); // Anade estado sin eliminar el anterior.
	void replaceState(GameState* pState); // Sustituye el estado anterior por uno nuevo.
	void popState(); // Elimina el estado actual sin reemplazarlo por otro.

	// Metodos que hacen cosas.
	void update();
	void render() const;
	void handleEvent();
};

