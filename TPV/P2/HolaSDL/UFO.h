#pragma once
#include "SceneObject.h"

const double TIEMPOAPARICION = 1000;

class UFO: public SceneObject
{
private:
	int _state;
	enum  states { VISIBLE, OCULTO, DESTRUIDO }; // Enumerado de los diferentes estados de la nave.
	char entity = 'u';
	double elapsedTime = 0;
public:
	UFO(Game* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime);
	~UFO();
	void state();
	void update();
	void const render();
	void const save(ofstream& fil);
};

