#pragma once
#include "Vector2D.h"
#include "texture.h"

const double TIEMPODISPARO = 1000;
class Game;
class Cannon
{
private:
	Point2D<double> posicion;
	Texture* textura = nullptr;
	Game* game = nullptr;
	int direccion = 0;
	int vidas;
	double elapsedTime = 0;
	SDL_Rect rect;

public:
	Cannon(Point2D<double> pos, Texture& tex, int vid, Game& gam);
	~Cannon();
	bool update();
	void hit();
	void render();
	void handleEvent(SDL_Event event);
	SDL_Rect getRect();

};

