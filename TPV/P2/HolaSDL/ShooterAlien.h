#pragma once
#include "Game.h"
#include "Alien.h"

class ShooterAlien : public Alien
{
private:
	double reloadTime;
	double maxShootTime = 30000;
	double minShootTime = 10000;
	double elapsedTime = 0;

public:
	ShooterAlien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot);
	~ShooterAlien();
	bool update() override;
	void shoot();
	double setTime();
};

