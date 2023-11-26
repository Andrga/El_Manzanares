#include "ShooterAlien.h"
ShooterAlien::ShooterAlien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot) :
	Alien(gam, pos, sub, tex, mot)
{}
ShooterAlien::~ShooterAlien() {}
bool ShooterAlien::update() 
{
	Alien::update();
	if (elapsedTime >= reloadTime)
	{
		cout << "Alien: pium pium" << endl;
		game->fireLaser(position, 'a');
		elapsedTime = 0.0;
		reloadTime = setTime();
	}
	return alive;
}
double ShooterAlien::setTime() 
{
	return reloadTime = game->getRandomRange(minShootTime, maxShootTime);
}