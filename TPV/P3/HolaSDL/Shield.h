#pragma once
#include "SceneObject.h"
#include "texture.h"

class Shield : public SceneObject
{
private:
	char entity = 'i';
	SDL_Renderer* renderer = nullptr;
	Texture* tex;

public:

	//Constructoras / destructoras
	Shield(PlayState* playST, Point2D<double> pos);
	~Shield();

	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
	void save(ostream& fil) const override;

	// Metodos de clase.
	void renderRect() const;
};

