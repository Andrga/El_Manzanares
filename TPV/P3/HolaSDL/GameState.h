#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "gameList.h"
#include "EventHandler.h"
#include <list>

class SDLApplication;
class Button;

class GameState
{
protected:
	GameList<GameObject, true> objs;
	std::list<EventHandler*> listeners;
	SDLApplication* sdlApp;

public:
	GameState(SDLApplication* _sdlApp) : sdlApp(_sdlApp) {}
	virtual ~GameState() = default;

	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void handleEvent(const SDL_Event& event) 
	{
		for(EventHandler* e:listeners){ e->handleEvent(event); }
	}
	virtual void save(std::ostream& fil) const = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;



	void addEventListener(EventHandler* lis) {
		listeners.push_back(lis);
	}
	void addObject(GameObject* obj) { objs.push_back(obj);}

	SDLApplication* getGame() const { return sdlApp; };
};
