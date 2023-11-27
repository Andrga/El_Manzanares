#pragma once
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class Game;

//template <class T>
class GameObject
{

protected:
	Game* game; // Puntero al juego.

public:
	GameObject(){}

	GameObject(Game* gam) : game(gam) {} // Constructora.

	virtual ~GameObject() = default; // Destructora.

	virtual void const render() = 0;

	virtual bool update() = 0;

	//virtual void const save() = 0;
};
