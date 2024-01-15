#include "GameStateMachine.h"
#include "checkML.h"

GameStateMachine::GameStateMachine()
{

}

GameStateMachine::~GameStateMachine() {
	while (!pilaEstados.empty()) {
		popState();
	}
	deleteStates();
}

#pragma region Updates
void GameStateMachine::update()
{
	if (!pilaEstados.empty())
	{
		pilaEstados.top()->update();
	}

	deleteStates();
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
			eliminaEstados.push(pilaEstados.top());
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
			eliminaEstados.push(pilaEstados.top());
			pilaEstados.pop();
		}
	}
}
#pragma endregion

void GameStateMachine::handleEvent(const SDL_Event& event)
{
	pilaEstados.top()->handleEvent(event);
}

void GameStateMachine::deleteStates() {

	const int cantStates = eliminaEstados.size();

	for (int i = 0; i < cantStates; i++)
	{
		delete eliminaEstados.top();
		eliminaEstados.pop();
	}
}