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
	SDL_Renderer* renderer = nullptr;
	Game* game = nullptr;
	bool hitted = false;
	SDL_Rect rect;
public:
	Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend);
	~Laser();
	void render();
	bool update();
	SDL_Rect getRect();
	void hit();
	bool canon();
};

