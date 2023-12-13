#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

class InfoBar : public GameObject
{
private:
	int score;
	Point2D<double> position;
	int cannonLives;
	const Texture* canTexture = nullptr; // Textura del cannon para la muestra de vidas restantes.
	SDL_Rect rect;
	Point2D<double> pos1, pos2, pos3;

public:

	InfoBar(PlayState* gam, Point2D<double> pos, const Texture* tex, int scr);

	~InfoBar();

	void update() override;

	void const render() override;

	void const save(ostream& fil)override;
};

