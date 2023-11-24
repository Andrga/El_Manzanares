#pragma once
#include "SDL.h"
#include "Alien.h"
#include "Mothership.h"
#include "UFO.h"
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "Bunker.h"

#include <SDL_image.h>
#include <vector>
#include <array>
#include <random>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;



const int NUM_TEXTURES = 4;
const string TEXTURE_ROOT = "assets/images/";
const string MAP_PATH = "assets/maps/original.txt";
const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;
const double velocidadAlien = 0.3;
const double velocidadCannon = 0.05;
const Vector2D<double> velocidadLaser(0, 0.05);
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS };

struct textureInfo
{
	string name;
	int rows;
	int cols;
};

const textureInfo texturesList[NUM_TEXTURES]
{
		textureInfo{"aliens",3,2},
		textureInfo{"bunker",1,4},
		textureInfo{"spaceship",1,1},
		textureInfo{"stars",1,1}
};

class Game
{
private:
	std::list<SceneObject*> entities; // Lista de entidades del juego.
	std::list<SceneObject*>::iterator it;
	//std::list<Cannon>::iterator itCannon;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	array<Texture*, NUM_TEXTURES> textures{	};
	Mothership* mother = new Mothership(1, 44);


	bool endGame = false;
	void readMap();
	void setupGame();
public:
	Game();
	~Game();
	void render();
	void update();
	void run();
	void handleEvent();

};

