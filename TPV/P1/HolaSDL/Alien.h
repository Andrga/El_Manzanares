#pragma once
#include "Vector2D.h"
#include "texture.h"
//#include "Game.h"

class Game;
class Alien
{
private:
	Point2D<double> posicion;
	int subtipo;
	Texture* textura = nullptr;
	Game* juego;
	int renderFrame = 0;
	SDL_Rect rect;
	bool hitted = false;

public:
	Alien();
	Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg);
	~Alien();
	void render();
	void hit();
	bool update();
	void animation();
	void bajar();
	SDL_Rect getRect();
};

