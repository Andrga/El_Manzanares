#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>

#include "gameList.h"

//using namespace std;

class SDLApplication;
class GameState;
class PlayState;

//template <class T>
class GameObject
{

protected:
	const SDLApplication* sdlAppl = nullptr; // Puntero al juego.
	GameState* gameST = nullptr; // Puntero al estado de juego
	GameList<GameObject, true>::anchor objAnch = nullptr;

public:

	GameObject(GameState* gamSt) :gameST(gamSt){}

	//GameObject(PlayState* gamSt) :gameST(gamSt) {}

	GameObject(SDLApplication* sdlap) : sdlAppl(sdlap) {
		gameST = nullptr;
	}
	virtual ~GameObject()= default; // Destructora.

	virtual void render() const = 0;

	virtual void update() = 0;

	virtual void save(std::ostream& fil) const = 0;
	
	void setListAnchor(GameList<GameObject, true>::anchor anc) { objAnch = anc; }

	const GameList<GameObject, true>::anchor& getListAnchor() const { return objAnch; }
};
