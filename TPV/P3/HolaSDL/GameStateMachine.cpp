#include "GameStateMachine.h"
#include "checkML.h"

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
			eliminaEstados.push_back(pilaEstados.top());
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
			eliminaEstados.push_back(pilaEstados.top());
			pilaEstados.pop();
		}
	}
}
#pragma endregion

void GameStateMachine::handleEvent(const SDL_Event& event)
{
	pilaEstados.top()->handleEvent(event);/*
	for (auto e : eliminaEstados)
	{
		delete e;

	}
	
	while (!eliminaEstados.empty()) {
		
		delete eliminaEstados.front();

	}*/
}