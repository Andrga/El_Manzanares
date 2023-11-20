#pragma once
#include <iostream>

class Game;

//template <class T>
class GameObject
{

protected:
	const Game* game; // Puntero al juego.

public:
	GameObject(){}
	GameObject(const Game& gam) : game(&gam) {} // Constructora.

	virtual ~GameObject() = default; // Destructora.

	virtual void const render() = 0;

	virtual bool update() = 0;

	virtual void const save() = 0;
};
