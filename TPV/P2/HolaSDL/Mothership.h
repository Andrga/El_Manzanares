#pragma once
#include "GameObject.h"
#include <vector>

class Mothership: public GameObject
{
private:
	int direction = 1;

public:
	Mothership(int dir); // Constructora.
	
	int getDirection() const; // Devuelve la direccion de movimiento.

	bool shouldMove();

	void canNotMove();

	int getAlienCount() const;

	void alienDied();

	void alienLanded();

	void haveLanded();
};

