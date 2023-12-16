#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "gameList.h"

//#include <list>

class SDLApplication;

class GameState
{
private:
	GameList<GameObject, true> objs;
	//list<EventHandler*> listeners;
	SDLApplication* sdlApp;

public:
	GameState(SDLApplication* _sdlApp) : sdlApp(_sdlApp) {}

	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void save(ostream& fil) const = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual string getStateID() const = 0;

	//virtual void addEventListener() = 0;
	//virtual void addObject() = 0;

	SDLApplication* getGame() const { return sdlApp; };
};
