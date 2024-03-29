#pragma once
#include "Vector2D.h"
#include "texture.h"

class Game;
class Alien
{
private:
	Point2D<double> posicion;
	Texture* textura = nullptr;
	Game* juego;
	SDL_Rect rect;
	double maxShootTime = 30000;
	double minShootTime = 10000;
	double elapsedShootTime = 0;
	int subtipo;
	int renderFrame = 0;
	bool hitted = false;

public:
	Alien();
	Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg);
	~Alien();
	void animation();
	void render();
	void hit();
	bool update();
	void bajar();
	SDL_Rect getRect();
};

