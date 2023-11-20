#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"


class SceneObject: public GameObject
{
protected:
	Point2D<int> position; // Posicion del elemento.
	int width; // Anchura.
	int height; // Altura.
	const Texture* texture;
	bool alive = false;
	SDL_Rect rect;

public:

	SceneObject(const Game& gam, Point2D<int> pos, /*int wid, int hei,*/ const Texture& tex) // Constructora.
		: GameObject(gam), position(pos), /*width(wid), height(hei),*/ texture(&tex) {} 
	
	virtual void hit(SDL_Rect rect, char c) = 0;
};

