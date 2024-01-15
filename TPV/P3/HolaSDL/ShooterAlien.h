#pragma once
#include "Alien.h"

constexpr int ID_SHOOTERALIEN = 2;

class ShooterAlien : public Alien
{
private:
	double reloadTime;
	double maxShootTime = 10000;
	double minShootTime = 500;
	double elapsedTime = 500;

public:

	//Constructoras / destructoras
	ShooterAlien(PlayState* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, double eTime);
	//~ShooterAlien();

	// Metodos heredados.
	void update() override;
	void save(std::ostream& fil) const override;
	
	//Metodos de clase.
	double setTime() const;

};

