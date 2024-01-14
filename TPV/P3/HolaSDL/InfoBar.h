#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

// Constante para el maximo numero de digitos de la puntuacion
const int MAX_DIGITS = 4;

// Vidas maximas del cannon.
constexpr int MAX_CANNON_LIVES = 3;

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
	~InfoBar();

	// Metodos heredados
	void update() override;
	void render() const override;
	void save(std::ostream& fil) const override;
};

