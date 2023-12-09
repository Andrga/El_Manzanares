#pragma once
#include "SceneObject.h"

class Bunker : public SceneObject
{
private:
	int lives = 4;
	int maxLives = 4;
	char entity = 'b';

public:
	Bunker();

	Bunker(Game* gam, int liv, Point2D<double> pos, const Texture* tex);

	~Bunker();
	
	void update() override;

	void const render() override;

	bool hit(SDL_Rect rect, char c) override;
	
	void const save(ofstream& fil)override;
};

