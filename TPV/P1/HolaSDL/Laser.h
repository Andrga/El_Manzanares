#pragma once
#include "Vector2D.h"
#include "texture.h"
class Laser
{
private:
	Point2D<double> posicion;
	Vector2D<double> velocidad;
	bool alien;
public:
	Laser(Point2D<double> pos, Vector2D<double> vel, bool al);
	~Laser();
	void render();
	bool update();


};

