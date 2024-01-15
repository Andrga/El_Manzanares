#pragma once
#include "GameObject.h"
#include <vector>

//class PlayState;

class Mothership : public GameObject
{
private:

	enum state : int { MOVE, STOP, SPIN, LANDED };
	state _state = MOVE;

	PlayState* playST = nullptr;

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

	// Constructora / Destructora.
	Mothership(PlayState* plST, SDLApplication* appl);

	// Metodos heredados
	void update() override;
	void render() const override;
	void save(std::ostream& fil) const override;

	// Metodos de clase
	void alienDied();
	void alienLanded();
	void haveLanded();
	void canNotMove();
	bool shouldMove();

	//Getters / Setters
	int getLevel() const { return level; }
	int getAlienCount() const;
	int getDirection() const { return direction; } // Devuelve la direccion de movimiento.

	void setMotherParams(int sta, int lev, int esp);
	void setAlienCount(int _nAliens);
};

