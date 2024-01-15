#pragma once
#include "SceneObject.h"

constexpr int ID_BUNKER = 4;

class Bunker : public SceneObject
{
private:
	int lives = 4;
	int maxLives = 4;
	char entity = 'b';

public:

	//Constructoras / destructoras
	Bunker(PlayState* gam, int liv, Point2D<double> pos, const Texture* tex);
	//~Bunker();
	
	// Metodos heredados
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(std::ostream& fil) const override;
};

