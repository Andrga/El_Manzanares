#pragma once
#include "SceneObject.h"

class Laser : public SceneObject
{
private:
	char entity = 'l';
	SDL_Renderer* renderer = nullptr;
	SDL_Color color;
	Vector2D<double> velocidad;



public:

	//Constructoras / destructoras
	Laser(PlayState* playST, Point2D<double> pos, char ent, Vector2D<double> vel);
	~Laser();
	
	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(std::ostream& fil) const override;

	// Metodos de clase.
	void renderRect() const;
};

