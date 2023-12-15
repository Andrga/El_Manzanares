#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "gameList.h"

#include <list>

class SDLApplication;

class GameState
{
private:
	GameList<GameObject, true> objs;
	//list<EventHandler*> listeners;
	SDLApplication* sdlapp;

public:
	GameState();

	virtual void update() = 0;
	virtual const void render() = 0;
	virtual void handleEvent(const SDL_Event&) = 0;
	virtual const void save(ostream&) = 0;

	virtual void addEventListener() = 0;
	virtual void addObject() = 0;

	void hasDied(GameList<GameObject, true>::anchor);
	SDLApplication* getGame() const { return sdlapp; };
};

