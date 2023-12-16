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
	virtual void render() const = 0;
	virtual void handleEvent(const SDL_Event&) = 0;
	virtual void save(ostream&) const = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual string getStateID() const = 0;

	virtual void addEventListener() = 0;
	virtual void addObject() = 0;

	SDLApplication* getGame() const { return sdlapp; };
};

