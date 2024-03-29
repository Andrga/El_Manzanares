#pragma once
#include "SceneObject.h"

const double TIEMPOAPARICION = 100;


class UFO : public SceneObject
{
private:

	enum  states { OCULTO, VISIBLE, DESTRUIDO }; // Enumerado de los diferentes estados de la nave.
	states UFOstate = OCULTO;
	char entity = 'a';
	double elapsedTime = 0;
	double aprearanceTime;
	Point2D<double>posInicial;
	int timer = 0, maxTimer = 7;
	bool reward = false;

public:

	//Constructoras / destructoras
	UFO(PlayState* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime);
	~UFO();

	// Metodos heredados.
	void update()override;
	void render() const override;
	void save(ostream& fil) const override;
	bool hit(SDL_Rect _rect, char c)override;

	// Metodos de clase.
	void reset();
};

