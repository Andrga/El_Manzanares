#include "checkML.h"
#include "ShooterAlien.h"
#include "PlayState.h"

ShooterAlien::ShooterAlien(PlayState* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, double eTime) :
	Alien(gam, pos, sub, tex, mot), elapsedTime(eTime)
{}

//ShooterAlien::~ShooterAlien() {}

void ShooterAlien::update()
{

	reloadTime = setTime();
	Alien::update();
	if (elapsedTime >= reloadTime)
	{
		//cout << "Alien: pium pium" << endl;
		//if (playST->getRandomRange(0, 10) < proporcionBombas) {
			//playST->fireBomb(position);
		//}
		//else {
			playST->fireLaser(position, 'a');
		//}

		elapsedTime = 0.0;
		reloadTime = setTime();
	}
	elapsedTime++;
	//cout << elapsedTime << endl;
}

double ShooterAlien::setTime() const
{
	return playST->getRandomRange(minShootTime, maxShootTime);
}

void ShooterAlien::save(std::ostream& fil) const // Guarda: tipo-posicion-subitpo-tiempoParaDisparar.
{
	fil << ID_SHOOTERALIEN << " " << position.getX() << " " << position.getY() << "  " << 0 << " " << elapsedTime << "\n";
}