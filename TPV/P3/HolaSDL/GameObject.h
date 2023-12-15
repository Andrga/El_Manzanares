#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>

using namespace std;

class SDLApplication;
class GameState;

//template <class T>
class GameObject
{

protected:
	const SDLApplication* sdlAppl = nullptr; // Puntero al juego.
	GameState* gameST = nullptr; // Puntero al estado de juego

public:

	GameObject() {};

	GameObject(SDLApplication* appl) : sdlAppl(appl) {} // Constructora.

	~GameObject() = default; // Destructora.

	virtual void render() const = 0;

	virtual void update() = 0;

	virtual void save(ostream& fil) const = 0;
};
