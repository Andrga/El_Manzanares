#pragma once
#include "GameObject.h"
#include <vector>

class Mothership: public GameObject
{
private:
	int direction = 1;

public:
	Mothership(int dir); // Constructora.
	
	const int getDirection(); // Devuelve la direccion de movimiento.

	bool shouldMove();

	void canNotMove();

	const int getAlienCount();

	void alienDied();

	void alienLanded();

	void haveLanded();
};

