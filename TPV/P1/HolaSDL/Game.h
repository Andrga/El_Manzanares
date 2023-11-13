#pragma once
#include "SDL.h"
#include "texture.h"
#include "Vector2D.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include <SDL_image.h>
#include <vector>
#include <array>
#include <random>

using namespace std;
static const int NUM_TEXTURES = 4;
static const string TEXTURE_ROOT = "assets/images/";
static const string MAP_PATH = "assets/maps/original.txt";
static const double SCRWIDTH = 800;
static const double SCRHEIGHT = 600;
static const double velocidadAlien = 0.01;
static const double velocidadCannon = 0.05;
static const Vector2D<double> velocidadLaser(0, 0.05);
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS };

class Game
{
private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	Cannon* cannon;
	vector<Alien*> aliens;
	vector<Bunker*> bunkers;
	vector<Laser*> lasers;
	array<Texture*, NUM_TEXTURES> textures{	};
	int direccionMovimiento = 1;
	int tiempoTrans = 0;
	mt19937_64 randomGenerator;

public:
	Game();
	~Game();
	void run();
	void render();
	void update();
	int getDirection();
	void cannotMove();
	void handleEvents();
	void fireLaser(Point2D<double>position, bool alieen);
	int getRandomRange(int min, int max);
	void colDetection(Laser* laser);

};
