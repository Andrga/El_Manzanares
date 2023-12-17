#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{
}

#pragma region Updates
void GameStateMachine::update()
{
	if (!pilaEstados.empty())
	{
		pilaEstados.top()->update();
	}
}

void GameStateMachine::render() const
{
	if (!pilaEstados.empty())
	{
		pilaEstados.top()->render();
	}
}
#pragma endregion


#pragma region Cambio de estados
void GameStateMachine::pushState(GameState* pState) {
	pilaEstados.push(pState);
	pilaEstados.top()->onEnter();
}

void GameStateMachine::replaceState(GameState* pState) {
	if (!pilaEstados.empty()) {
		if (pilaEstados.top() == pState)
		{
			return;
		}
		if (pilaEstados.top()->onExit())
		{
			delete pilaEstados.top();
			pilaEstados.pop();
		}
		pilaEstados.push(pState);
		pilaEstados.top()->onEnter();
	}
}

void GameStateMachine::popState()
{
	if (!pilaEstados.empty())
	{
		if (pilaEstados.top()->onExit())
		{
			delete pilaEstados.top();
			pilaEstados.pop();
		}
	}
}
#pragma endregion

void GameStateMachine::handleEvent(SDL_Event& event)
{
	pilaEstados.top()->handleEvent(event);

	/*  AQUI VA EL GUARDADO NO LO BORRES (no esta hecho pero bueno :/)
	string num;
	cout << "Numero de guardado de partida:";
	cin >> num;

	ofstream file;
	file.open("assets/maps/guardado" + num + ".txt");
	save(file);

	file.close();*/
}