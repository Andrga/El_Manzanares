#pragma once
#include <iostream>
#include <fstream>
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

	virtual void update() = 0;

	virtual void const save(ofstream& fil) = 0;
};
