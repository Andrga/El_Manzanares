#pragma once
#include "Vector2D.h"
#include "texture.h"
class Game;
class Laser
{
private:
	Point2D<double> posicion;
	Vector2D<double> velocidad;
	bool alien;
	SDL_Rect rectangulo;
	SDL_Renderer* renderer = nullptr;
	Game* game = nullptr;
public:
	Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend);
	~Laser();
	void render();
	bool update();
};

