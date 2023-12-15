#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

class PlayState;

class InfoBar : public GameObject
{
private:
	int score;
	Point2D<double> position;
	PlayState* playST;
	int cannonLives;
	const Texture* canTexture = nullptr; // Textura del cannon para la muestra de vidas restantes.
	SDL_Rect rect;
	Point2D<double> pos1, pos2, pos3;

public:

	//Constructoras / destructoras
	InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, const Texture* canTex, int scr);
	~InfoBar();

	// Metodos heredados
	void update() override;
	void render() const override;
	void save(ostream& fil) const override;
};

