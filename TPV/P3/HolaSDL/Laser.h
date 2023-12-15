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
	SDL_Renderer* renderer = nullptr;
	SDL_Color color;
	Vector2D<double> velocidad;



public:

	//Constructoras / destructoras
	Laser(PlayState* playST, Point2D<double> pos, char ent, Vector2D<double> vel, SDL_Renderer* _renderer);
	~Laser();
	
	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(ostream& fil) const override;

	// Metodos de clase.
	void renderRect() const;
};

