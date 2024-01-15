#pragma once
#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "texture.h"

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
	GameList<SceneObject>::anchor scAnch; // interador identificador


public:

	SceneObject(PlayState* plST, Point2D<double> pos, int wid, int hei, const Texture* tex); // Constructora.

	//Metodos heredados
	virtual void update();
	virtual void render() const;
	virtual void save(std::ostream& fil) const;
	SDL_Rect getRect();

	virtual bool hit(SDL_Rect _rect, char c);

	virtual void setListAnchor(const GameList<SceneObject, false>::anchor& anc) { scAnch = anc; }
};

