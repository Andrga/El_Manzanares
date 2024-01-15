#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"

constexpr int ID_ALIEN(1);

class Alien : public SceneObject
{
private:

	int subtipo; // Subtipo de alien.
	Mothership* mothership = nullptr; // Puntero a mothership.
	double posYAnt = 0; // Posicion Y anterior
	char entity = 'a';

	int nombre;

	bool move = false;

	//Animation parameters
	int renderFrame = 0;
	int changeSprTime = 1000;
	int elapsedTime;

	// Cambiar el renderFrame.
	void animation() { renderFrame == 0 ? renderFrame = 1 : renderFrame = 0; }



public:

	//Constructoras / destructoras
	Alien(PlayState* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot);
	//~Alien();

	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(std::ostream& fil) const override;
};


