#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"


class SceneObject : public GameObject
{
protected:
	Point2D<double> position; // Posicion del elemento.
	int width; // Anchura.
	int height; // Altura.
	const Texture* texture = nullptr;
	bool alive = true;
	SDL_Rect* rect;
	list<SceneObject*>::iterator ite;

public:

	SceneObject(Game* gam, Point2D<double> pos, int wid, int hei, const Texture* tex) // Constructora.
		: GameObject(gam), position(pos), width(wid), height(hei), texture(tex)
	{
		rect = new SDL_Rect;
		rect->w = wid;
		rect->h = hei;
	}

	virtual bool hit(SDL_Rect* _rect, char c) = 0;

	void setListIterator(list<SceneObject*>::iterator& it)
	{
		ite = it;
	}
};

