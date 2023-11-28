#pragma once
#include "SceneObject.h"
//#include "Game.h"

const double TIEMPODISPARO = 75;

class Cannon : public SceneObject
{
private:
	int lives = 3; // Numero de vidas del cannon.
	int direction = 0; // Direcciones: -1 (izquierda), 0 (parado), 1 (derecha).
	double elapsedTime = 0;
	char entity = 'c';


public:
	Cannon(Game* gam, Point2D<double> pos, const Texture* tex, int liv, int eTime);

	~Cannon();

	void update() override;

	void const render() override;

	int getLives() {
		return lives;
	}
	void handleEvents(SDL_Event event);

	bool hit(SDL_Rect* rect, char c)override;

	//list<SceneObject*>::iterator getIterator() { return ownIte; }

	void const save(ofstream& fil)override;
};

