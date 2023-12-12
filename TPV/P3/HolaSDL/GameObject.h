#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>

using namespace std;

class PlayState;

//template <class T>
class GameObject
{

protected:
	SDLApplication* game; // Puntero al juego.

public:
	GameObject(){}

	GameObject(SDLApplication* gam) : game(gam) {} // Constructora.

	virtual ~GameObject() = default; // Destructora.

	virtual void const render() = 0;

	virtual void update() = 0;

	virtual void const save(ofstream& fil) = 0;
};
