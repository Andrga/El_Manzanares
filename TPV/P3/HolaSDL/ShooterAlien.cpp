#include "checkML.h"
#include "ShooterAlien.h"
#include "PlayState.h"

ShooterAlien::ShooterAlien(PlayState* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, double eTime) :
	Alien(gam, pos, sub, tex, mot), elapsedTime(eTime)
{}

ShooterAlien::~ShooterAlien() {}

void ShooterAlien::update() 
{

	reloadTime = setTime();
	Alien::update();
	if (elapsedTime >= reloadTime)
	{
		//cout << "Alien: pium pium" << endl;
		playST->fireLaser(position, 'a');
		elapsedTime = 0.0;
		reloadTime = setTime();
	}
	elapsedTime++;
	//cout << elapsedTime << endl;
}

double ShooterAlien::setTime() 
{
	return reloadTime = playST->getRandomRange(minShootTime, maxShootTime);
}

void ShooterAlien::save(ostream& fil) const // Guarda: tipo-posicion-subitpo-tiempoParaDisparar.
{
	fil << 2 << " " << position.getX() << " " << position.getY() << "  " << 0 << " " << elapsedTime << "\n";
}