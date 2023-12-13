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
	PlayState* game; // Puntero al juego.

public:
	GameObject() {};

	GameObject(PlayState* gam) : game(gam) {} // Constructora.

	virtual ~GameObject() = default; // Destructora.

	virtual void const render() = 0;

	virtual void update() = 0;

	virtual void const save(ostream& fil) = 0;
};
