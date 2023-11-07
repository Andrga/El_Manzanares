#pragma once
#include "Vector2D.h"
#include "texture.h"
class Game;
class Cannon
{
private:
	Point2D<double> posicion;
	Texture* textura = nullptr;
	Game* game = nullptr;
	int direccion = 0;
	int vidas;
	int tiempo;

public:
	Cannon(Point2D<double> pos, Texture& tex, int vid, Game& gam);
	bool update();
	bool hit();
	void render();
	void handleEvent(SDL_Event event);

};

