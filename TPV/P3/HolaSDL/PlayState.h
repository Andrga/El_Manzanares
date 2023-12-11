#pragma once
#include "GameState.h"
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

#include <random>
class PlayState : public GameState
{
private:
	std::list<list<SceneObject*>::iterator> itElims; //lista de iteradores objetos a eliminar
	std::list<SceneObject> entities;

	Cannon* canion = nullptr;
	Mothership* mother = mother = new Mothership(this);;
	InfoBar* info = nullptr;
	mt19937_64 randomGenerator;

	bool endGame = false;
	bool _gameOver = false;

	string map = MAP_PATH;
	uint32_t frameTime;
	uint32_t startTime;

	void readMap();

	int score = 0;
public:

	void update() override;
	const void render() override;
	void handleEvent() override;

	int getRandomRange(int min, int max);

	bool damage(SDL_Rect* _rect, char c);

	void fireLaser(Point2D<double>& position, char c);

	void gameOver();

	void save(string _saveNum);

	void hasDied(list<SceneObject*>::iterator& ite);

	void cargado();

	void invencible();

	int getCannonLives();

	void addScore(int points);

	int returnScore() { return score; }

	double getCannonYPos() { return canion->getPos().getY(); }

};
