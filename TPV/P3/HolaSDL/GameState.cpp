#include "GameState.h"
#include "checkML.h"
using namespace std;

void GameState::update() {
	for (auto& e : objs) {
		e.update();
	}
}
void GameState::render() const {
	for (auto& e : objs) {
		e.render();
	}

}


void GameState::addObject(GameObject* obj) {
	objs.push_back(obj);
}

void GameState::eraseObject(GameList<GameObject, true>::anchor anch)
{
	objs.erase(anch);
}

void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* e : listeners) { e->handleEvent(event); }
}