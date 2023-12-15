#pragma once
#include "PlayState.h"
#include "Alien.h"

class ShooterAlien : public Alien
{
private:
	double reloadTime;
	double maxShootTime = 10000;
	double minShootTime = 10;
	double elapsedTime = 0;

public:

	//Constructoras / destructoras
	ShooterAlien(PlayState* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, double eTime);
	~ShooterAlien();

	// Metodos heredados.
	void update() override;
	void save(ostream& fil) const override;
	
	//Metodos de clase.
	void shoot();
	double setTime();

};

