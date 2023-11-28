#pragma once
#include "SDL.h"
#include "Alien.h"
#include "Mothership.h"
#include "UFO.h"
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "Bunker.h"
#include "Laser.h"
#include"ShooterAlien.h"

#include <SDL_image.h>
#include <vector>
#include <array>
#include <random>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

const int NUM_TEXTURES = 6;
const string TEXTURE_ROOT = "assets/images/";
const string MAP_PATH = "assets/maps/";
const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;
const double velocidadAlien = 0.05;
const double velocidadCannon = 0.5;
const Vector2D<double> velocidadLaser(0, 0.5);
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS, LASER, UFO };
const double FRAMERATE = 60;
const double TIMEBETWEENFRAMES = 100 / FRAMERATE;

struct textureInfo
{
	string name;
	int rows;
	int cols;
};

const textureInfo texturesList[NUM_TEXTURES]
{
		textureInfo{"aliens", 3, 2},
		textureInfo{"bunker", 1, 4},
		textureInfo{"spaceship", 1, 1},
		textureInfo{"stars",1, 1},
		textureInfo{"Laser",1, 1},
		textureInfo{"Ufo", 1, 2}
};

class Game
{
private:
	std::list<SceneObject*> entities; // Lista de entidades del juego.
	//std::list<SceneObject*>::iterator it;
	std::list<list<SceneObject*>::iterator> itElims; //lista de iteradores objetos a eliminar

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	array<Texture*, NUM_TEXTURES> textures{	};
	Mothership* mother = nullptr;
	mt19937_64 randomGenerator;

	string map = MAP_PATH;
	int nAliens = 0;
	uint32_t frameTime;
	uint32_t startTime;
	bool endGame = false;
	bool _gameOver = false;
	void readMap();
	void setupGame();

public:
	Game();

	~Game();

	void render();

	void update();

	void run();

	void handleEvent();

	int getRandomRange(int min, int max);

	bool damage(SDL_Rect* _rect, char c);

	void fireLaser(Point2D<double> &position, char c);

	void gameOver();

	void save();
	
	void hasDied(list<SceneObject*>::iterator& ite);
	
	void cargado();
};

