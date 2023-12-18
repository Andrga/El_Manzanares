#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include <array>

class InfoBar : public GameObject
{
private:
	int score;
	Point2D<double> position;
	PlayState* playST;
	int cannonLives;
	Texture* canTexture;

	SDL_Rect* canVid;
	array<SDL_Rect, 4> cifrPunt;

public:

	//Constructoras / destructoras
	InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, int scr);
	~InfoBar();

	// Metodos heredados
	void update() override;
	void render() const override;
	void save(ostream& fil) const override;

	void renderScore();
};

