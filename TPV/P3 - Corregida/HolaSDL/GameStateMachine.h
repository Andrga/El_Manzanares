#pragma once
#include <iostream>
#include <stack>

#include "GameState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <list>

//using namespace std;
class GameStateMachine
{
protected:
	std::stack<GameState*> pilaEstados;
	std::stack<GameState*> eliminaEstados;
public:
	GameStateMachine();
	~GameStateMachine();

	// Metodos para manejar estados.
	void pushState(GameState* pState); // Anade estado sin eliminar el anterior.
	void replaceState(GameState* pState); // Sustituye el estado anterior por uno nuevo.
	void popState(); // Elimina el estado actual sin reemplazarlo por otro.
	void deleteStates();

	// Metodos que hacen cosas.
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

