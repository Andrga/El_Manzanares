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
	void pushState();
	void replaceState();
	void popState();

	// Metodos que hacen cosas.
	void update();
	void render() const;
	void handleEvent();
};

