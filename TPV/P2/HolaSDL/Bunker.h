#pragma once
#include "SceneObject.h"

class Bunker : public SceneObject
{
private:
	int lives = 4;

public:
	Bunker();
	Bunker(const Game* gam, int liv, Point2D<double> pos, const Texture* tex);
	~Bunker();
	bool update() override;
	void const render() override;
	void hit(SDL_Rect rect, char c) override;
};

