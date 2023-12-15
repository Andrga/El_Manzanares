#pragma once
#include "SceneObject.h"

const double TIEMPOAPARICION = 100;


class UFO : public SceneObject
{
private:

	enum  states { OCULTO, VISIBLE, DESTRUIDO }; // Enumerado de los diferentes estados de la nave.
	states UFOstate = OCULTO;
	char entity = 'u';
	double elapsedTime = 0;
	double aprearanceTime;
	Point2D<double>posInicial;
	int timer = 0, maxTimer = 7;

public:

	//Constructoras / destructoras
	UFO(PlayState* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime);
	~UFO();

	// Metodos heredados.
	void update()override;
	void const render()override;
	void const save(ostream& fil)override;
	bool hit(SDL_Rect _rect, char c)override;

	// Metodos de clase.
	void reset();
};

