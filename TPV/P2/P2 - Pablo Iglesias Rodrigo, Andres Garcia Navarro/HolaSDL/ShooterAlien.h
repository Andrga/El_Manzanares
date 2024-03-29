#pragma once
#include "Game.h"
#include "Alien.h"

class ShooterAlien : public Alien
{
private:
	double reloadTime;
	double maxShootTime = 10000;
	double minShootTime = 10;
	double elapsedTime = 0;

public:
	ShooterAlien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, double eTime);

	~ShooterAlien();

	void update() override;
	
	void shoot();

	double setTime();

	void const save(ofstream& fil)override;
};

