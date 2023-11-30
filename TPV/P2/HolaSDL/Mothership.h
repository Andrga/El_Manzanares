#pragma once
#include "GameObject.h"
#include <vector>

class Mothership : public GameObject
{
private:

	enum state : int { MOVE, STOP, SPIN, LANDED };
	state _state = MOVE;

	// Contador para moverse.
	int maxTime = 10;
	int elapsedTime = 0;

	// Direccion de los aliens.
	int direction = 1;
	int nAliens = 44;

	// Aliens que han llamado al mothership para comprobar si moverse.
	int aliensReistrados = 0;

	// Nivel de altura.
	int level = 0;
public:
	Mothership(Game* gam);

	int getDirection() const { return direction; } // Devuelve la direccion de movimiento.

	bool shouldMove();

	void canNotMove();

	int getAlienCount() const;

	void alienDied();

	void alienLanded();

	bool haveLanded();

	int getLevel() { return level; }

	void update() override;

	void const render() override;

	void const save(ofstream& fil)override;

	void setMotherParams(int sta, int lev, int esp);

	void setAlienCount(int _nAliens);
};

