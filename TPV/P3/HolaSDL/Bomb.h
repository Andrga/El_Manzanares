#pragma once
#include "SceneObject.h"
#include "texture.h"

constexpr int ID_BOMBA = 4;

class Bomb : public SceneObject
{
private:
	char entity = 'a';
	int vidas = 2;
	SDL_Renderer* renderer = nullptr;
	Texture* tex;


public:

	//Constructoras / destructoras
	Bomb(PlayState* playST, Point2D<double> pos, int vid = 2);
	//~Bomb();

	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(std::ostream& fil) const override;
};



