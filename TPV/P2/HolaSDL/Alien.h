#pragma once
#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"


class Game;
class Alien : public SceneObject
{
private:

	int subtipo;
	Mothership* mothership = nullptr; // Puntero a mothership.
	char entity = 'a';

	//Animation parameters
	int renderFrame = 0;
	int changeSprTime;
	int elapsedTime;
	void animation();



public:
	Alien();
	Alien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot);
	~Alien();
	bool update() override;
	const void render() override;
	void hit(SDL_Rect* rect, char c) override;
	//list<SceneObject*>::iterator getIterator() { return ite; }

	//void bajar();
};


