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
#include "Bomb.h"
#include "Reward.h"
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

//using namespace std;

const std::string MAP_PATH = "assets/maps/";


const double velocidadAlien = 5;
const double velocidadBomb = 5;
const double velocidadCannon = 10;
const Vector2D<double> velocidadLaser(0, 5);
const int proporcionBombas = 5;
const int velocidadReward = 4;

class PlayState : public GameState
{
private:
	GameList<SceneObject, false> entities;
	SDL_Renderer* renderer;


	Cannon* canion = nullptr;
	Mothership* mother = new Mothership(this, getGame());
	InfoBar* info = nullptr;
	std::mt19937_64 randomGenerator;

	std::string map = MAP_PATH;
	int score = 0;

	void readMap();

public:
	PlayState(SDLApplication* _sdlApp, bool guardado);

	~PlayState();

	//Metodos overrided
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& fil) const override;

	//Estados
	bool onEnter() override;
	bool onExit() override;
	std::string getStateID() const override { return"PlayST"; }

	//Metodos de clase
	bool damage(SDL_Rect _rect, char c);
	void fireLaser(const Point2D<double>& position, char c);
	void fireBomb(const Point2D<double>& position);
	void fireReward(const Point2D<double>& position);
	bool mayGrantReward(SDL_Rect rect);
	void gameOver();
	void hasDied(GameList<SceneObject, false>::anchor anch);
	void cargado();
	void invencible() { canion->setInvincible(); }
	void addScore(int points) { score += points; }
	void hasDied(GameList<GameObject, true>::anchor);
	void saveGame();

	//Getters
	int getRandomRange(int min, int max);
	int getCannonLives() const { return canion->getLives(); }
	int returnScore() const { return score; }
	const double getCannonYPos() const { return canion->getPos().getY(); }
};

