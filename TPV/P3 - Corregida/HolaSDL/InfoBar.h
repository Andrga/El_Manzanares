#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"


const int MAX_DIGITS = 4,					// Constante para el maximo numero de digitos de la puntuacion
		MAX_CANNON_LIVES = 3,				// Vidas maximas del cannon.
		DIGIT_DIV = 10,						// Divisor de digitos
		DIGIT_PITH = 50,					// Separacion de digitos.
		X_OFFSET = 400, Y_OFFSET = 10,		// Offset para que empiecen en el lado derecho y abajo las cifras de la puntuacion
		ID_INFOBAR = 7;						// ID de guardado

class InfoBar : public GameObject
{
private:
	int score;
	Point2D<double> position;
	PlayState* playST;
	int cannonLives;
	Texture* canTexture;
	Texture* numTexture;

	SDL_Rect canVid[MAX_CANNON_LIVES];
	SDL_Rect cifrPunt[MAX_DIGITS];

public:

	//Constructoras / destructoras
	InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, int scr);
	//~InfoBar();

	// Metodos heredados
	void update() override;
	void render() const override;
	void save(std::ostream& fil) const override;
};

