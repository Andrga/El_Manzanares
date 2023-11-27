#pragma once
#include "SceneObject.h"

class Laser : public SceneObject
{
private:
	/*Point2D<double> posicion;
	bool alien;
	SDL_Renderer* renderer = nullptr;
	Game* game = nullptr;
	bool hitted = false;
	SDL_Rect rect;*/
	char entity = 'l';
	Vector2D<double> velocidad;



public:
	Laser(Game* gam, Point2D<double> pos, const Texture* tex, char ent, Vector2D<double> vel);

	~Laser();

	bool update() override;

	void const render() override;

	bool hit(SDL_Rect* rect, char c) override;
};

