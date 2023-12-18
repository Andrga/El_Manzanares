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
	Texture* numTexture;

	SDL_Rect* canVid;
	SDL_Rect* cifrPunt;

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

