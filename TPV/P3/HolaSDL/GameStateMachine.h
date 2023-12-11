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
	void pushState();
	void replaceState();
	void popState();
	void update();
	void render();
	void handleEvent();
};

