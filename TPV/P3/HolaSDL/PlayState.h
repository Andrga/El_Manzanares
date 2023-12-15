#pragma once
#include "SDL.h"
//#include "SDLApplication.h"
#include "Alien.h"
#include "Mothership.h"
#include "UFO.h"
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "Bunker.h"
#include "Laser.h"
#include "ShooterAlien.h"
#include "InfoBar.h"

#include "GameState.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"


//#include <SDL_image.h>
#include <vector>
#include <array>
#include <random>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

const string MAP_PATH = "assets/maps/";
const double velocidadAlien = 100;
const double velocidadCannon = 15;
const Vector2D<double> velocidadLaser(0, 10);
const double FRAMERATE = 20;
const double TIMEBETWEENFRAMES = 1000 / FRAMERATE;

class PlayState : public GameState
{
private:
	GameList<SceneObject, false> entities;
	//std::list<SceneObject*> entities; // Lista de entidades del juego.
	//std::list<SceneObject*>::iterator it;
	//std::list<list<SceneObject*>::iterator> itElims; //lista de iteradores objetos a eliminar

	//SDL_Window* window = nullptr;
	//SDL_Renderer* renderer = nullptr;
	//array<Texture*, NUM_TEXTURES> textures;
	SDL_Renderer* renderer;


	Cannon* canion = nullptr;
	Mothership* mother = new Mothership(this, getGame());
	InfoBar* info = nullptr;
	mt19937_64 randomGenerator;

	string map = MAP_PATH;
	uint32_t frameTime;
	uint32_t startTime;
	bool endGame = false;
	bool _gameOver = false;
	int score = 0;

	void readMap();

public:
	PlayState(SDL_Renderer* rend);

	~PlayState();

	//Metodos overrided
	const void render() override;
	void update() override;
	void run();
	void handleEvent();
	const void save(ostream& file) override;

	//Metodos de clase
	bool damage(SDL_Rect _rect, char c);
	void fireLaser(Point2D<double>& position, char c);
	void gameOver();
	void hasDied(GameList<SceneObject, false>::anchor anch);
	void cargado();
	void invencible() { canion->setInvincible(); }
	void addScore(int points) { score += points; }

	//Getters
	const int getRandomRange(int min, int max) { return  uniform_int_distribution<int>(min, max)(randomGenerator); }
	const int getCannonLives() { return canion->getLives(); }
	const int returnScore() { return score; }
	const double getCannonYPos() { return canion->getPos().getY(); }
};

