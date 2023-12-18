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
#include "ShooterAlien.h"
#include "InfoBar.h"
#include "SceneObject.h"


#include "GameState.h"
#include "EventHandler.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"

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
const double velocidadAlien = 20;
const double velocidadCannon = 10;
const Vector2D<double> velocidadLaser(0, 5);

class PlayState : public GameState
{
private:
	GameList<SceneObject, false> entities;
	SDL_Renderer* renderer;


	Cannon* canion = nullptr;
	Mothership* mother = new Mothership(this, getGame());
	InfoBar* info = nullptr;
	mt19937_64 randomGenerator;

	string map = MAP_PATH;
	int score = 0;

	void readMap();

public:
	PlayState(SDLApplication* _sdlApp, bool guardado);

	~PlayState();

	//Metodos overrided
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(ostream& fil) const override;

	//Estados
	bool onEnter() override;
	bool onExit() override;
	string getStateID() const override { return"PlayST"; }

	//Metodos de clase
	bool damage(SDL_Rect _rect, char c);
	void fireLaser(Point2D<double>& position, char c);
	void gameOver();
	void hasDied(GameList<SceneObject, false>::anchor anch);
	void cargado();
	void invencible() { canion->setInvincible(); }
	void addScore(int points) { score += points; }
	void hasDied(GameList<GameObject, true>::anchor);
	void saveGame();

	//Getters
	const int getRandomRange(int min, int max) { return  uniform_int_distribution<int>(min, max)(randomGenerator); }
	const int getCannonLives() { return canion->getLives(); }
	const int returnScore() { return score; }
	const double getCannonYPos() { return canion->getPos().getY(); }
};

