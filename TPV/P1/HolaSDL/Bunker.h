#pragma once
#include "Vector2D.h"
#include "texture.h"
class Bunker
{
private:
	int maxVidas;
	int actVidas = 0;
	Point2D<double> posicion;
	Texture* textura;
	SDL_Rect rect;
public:
	Bunker(); // Cosntructor por defecto.
	Bunker(Point2D<double> pos, int vid, Texture& tex); // Constructor.
	~Bunker();
	void render();
	bool update(); // Update.
	void hit();
	SDL_Rect getRect();
};