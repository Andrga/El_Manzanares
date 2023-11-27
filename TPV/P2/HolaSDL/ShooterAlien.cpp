#include "ShooterAlien.h"
ShooterAlien::ShooterAlien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, int nomb) :
	Alien(gam, pos, sub, tex, mot, nomb)
{}

ShooterAlien::~ShooterAlien() {}

bool ShooterAlien::update() 
{

	reloadTime = setTime();
	Alien::update();
	if (elapsedTime >= reloadTime)
	{
		//cout << "Alien: pium pium" << endl;
		game->fireLaser(position, 'a');
		elapsedTime = 0.0;
		reloadTime = setTime();
	}
	elapsedTime++;
	//cout << elapsedTime << endl;
	return alive;
}

double ShooterAlien::setTime() 
{
	return reloadTime = game->getRandomRange(minShootTime, maxShootTime);
}

void const ShooterAlien::save(ofstream& fil) // Guarda: tipo-posicion-tiempoParaDisparar.
{
	fil << 2 << " " << position.getX() << " " << position.getY() << "  " << elapsedTime << "\n";
}