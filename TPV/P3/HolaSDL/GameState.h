#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "Game.h"

#include <list>
class GameState
{
private:
	GameList<GameObject, true> objs;
	//list<EventHandler*> listeners;
	Game* game;

public:
	GameState();

	virtual void update() = 0;
	virtual const void render() = 0;
	virtual void handleEvent() = 0;
	virtual void addEventListener() = 0;
	virtual void addObject() = 0;
};

