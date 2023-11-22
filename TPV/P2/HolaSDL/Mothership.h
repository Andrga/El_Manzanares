#pragma once
#include "GameObject.h"
#include <vector>

class Mothership: public GameObject
{
private:
	int direction = 1;
	int nAliens = 44;
public:
	Mothership(int dir, int aAl); // Constructora.
	
	int getDirection() const { return direction; } // Devuelve la direccion de movimiento.

	bool shouldMove();

	void canNotMove();

	int getAlienCount() const;

	void alienDied();

	void alienLanded();

	void haveLanded();
	bool update() override;
	void const render() override;
};

