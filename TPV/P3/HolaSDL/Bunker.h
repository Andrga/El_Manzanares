#pragma once
#include "SceneObject.h"

class Bunker : public SceneObject
{
private:
	int lives = 4;
	int maxLives = 4;
	char entity = 'b';

public:

	//Constructoras / destructoras
	Bunker();
	Bunker(PlayState* gam, int liv, Point2D<double> pos, const Texture* tex);
	~Bunker();
	
	// Metodos heredados
	void update() override;
	void const render() override;
	bool hit(SDL_Rect rect, char c) override;
	void const save(ostream& fil)override;
};

