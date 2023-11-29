#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

class InfoBar : public GameObject
{
private:
	int score;
	Point2D<double> position;
	const Texture* canTexture = nullptr;
	int CannonLives = 3;
	SDL_Rect* rect;

public:

	InfoBar(Game* gam, Point2D<double> pos, const Texture* tex, int scr);

	~InfoBar();

	void update() override;

	void const render() override;

	void const save(ofstream& fil)override;
};

