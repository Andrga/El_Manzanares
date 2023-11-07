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

public:
	Alien() = default;
	Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg);
	~Alien();
	void render();
	bool hit();
	bool update();
	void animation();
	void bajar();
};

