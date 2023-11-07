#pragma once
#include "Vector2D.h"
#include "texture.h"
class Laser
{
private:
	Point2D<double> posicion;
	Vector2D<int> velocidad;
	bool alien;
public:
	Laser();
	void render();
	void update();


};

