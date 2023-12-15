#pragma once
#include "GameObject.h"
#include "SDLApplication.h"
#include "gameList.h"
#include "Vector2D.h"
#include "texture.h"

class PlayState;

class SceneObject : public GameObject
{
protected:
	PlayState* playST = nullptr;

	Point2D<double> position; // Posicion del elemento.
	int width; // Anchura.
	int height; // Altura.
	const Texture* texture = nullptr;
	//bool alive = true;
	SDL_Rect rect;
	GameList<SceneObject, false>::anchor ownAnch;

public:

	SceneObject(PlayState* plST, Point2D<double> pos, int wid, int hei, const Texture* tex) // Constructora.
		: playST(plST), position(pos), width(wid), height(hei), texture(tex)
	{
		rect.w = wid;
		rect.h = hei;
	}

	//Metodos heredados
	void render() const override;
	void update() override;
	void save(ostream& fil) const override;

	virtual bool hit(SDL_Rect _rect, char c);

	void setListAnchor(GameList<SceneObject, false>::anchor& anc) { ownAnch = anc; }
};

