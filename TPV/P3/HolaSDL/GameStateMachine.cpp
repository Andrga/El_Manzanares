#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState) {
	pilaEstados.push(pState);
	pilaEstados.top()->onEnter();
}
void GameStateMachine::replaceState(GameState* pState) {
	if (!pilaEstados.empty()){
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