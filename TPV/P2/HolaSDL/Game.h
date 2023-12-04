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
#include "InfoBar.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"


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

const int NUM_TEXTURES = 5;
const string TEXTURE_ROOT = "assets/images/";
const string MAP_PATH = "assets/maps/";
const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;
const double velocidadAlien = 100;
const double velocidadCannon = 15;
const Vector2D<double> velocidadLaser(0, 10);
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS, UFOT };
const double FRAMERATE = 20;
const double TIMEBETWEENFRAMES = 1000 / FRAMERATE;

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
		textureInfo{"spaceship", 1, 2},
		textureInfo{"stars",1, 1},
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
	Cannon* canion = nullptr;
	Mothership* mother = mother = new Mothership(this);;
	InfoBar* info = nullptr;
	mt19937_64 randomGenerator;

	string map = MAP_PATH;
	uint32_t frameTime;
	uint32_t startTime;
	bool endGame = false;
	bool _gameOver = false;
	void readMap();
	void setupGame();
	int iu = 0;
	int score = 0;
public:
	Game(SDL_Window* win);

	~Game();

	void render();

	void update();

	void run();

	void handleEvent();

	int getRandomRange(int min, int max);

	bool damage(SDL_Rect* _rect, char c);

	void fireLaser(Point2D<double>& position, char c);

	void gameOver();

	void save();

	void hasDied(list<SceneObject*>::iterator& ite);

	void cargado();

	void invencible();

	int getCannonLives();

	void addScore(int points);

	int returnScore() { return score; }

	double getCannonYPos() { return canion->getPos().getY(); }
};

