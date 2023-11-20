#pragma once
#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"


class Game;
class Alien: public SceneObject
{
private:

	int subtipo;
	int renderFrame = 0;
	const Mothership* mothership; // Puntero a mothership.
	
public:
	Alien();
	Alien(Point2D<int> pos, int subt, const Texture& tex, const Game& gam, const Mothership& mot);
	~Alien();
	bool update() override;
	const void render() override;
	void hit(SDL_Rect rect, char c) override;
	
	
	
	
	/*void animation();
	void bajar();*/
};


