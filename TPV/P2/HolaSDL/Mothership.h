#pragma once
#include "GameObject.h"
#include <vector>

class Mothership: public GameObject
{
private:
	int direction = 1;
	int nAliens = 44;
public:
	Mothership(int dir); // Constructora.
	
	int getDirection() const { return direction; } // Devuelve la direccion de movimiento.

	bool shouldMove();

	void canNotMove();

	int getAlienCount() const;

	void alienDied();

	void alienLanded();

	void haveLanded();

	void update() override;

	void const render() override;
	
	void const save(ofstream& fil)override;
	
	void setAlienCount(int _nAliens);
};

