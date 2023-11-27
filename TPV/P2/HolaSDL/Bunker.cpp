#include "Bunker.h"
#include "game.h"


Bunker::Bunker(Game *gam, int liv, Point2D<double> pos, const Texture* tex)
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), maxLives(liv)
{
	rect->x = position.getX();
	rect->y = position.getY();
	lives = maxLives;

}

Bunker::~Bunker() {}

bool Bunker::hit(SDL_Rect *_rect, char c) 
{
//	//lives--;
//	alive = lives <= 0;
//	//cout << "ay ay ay" << lives;
//	return false;

	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			cout << "Bunker: hit" << endl;
			//game->hasDied(ownIte);
			lives--;
			return true;
		}
	}
	return false;
}

bool Bunker::update() 
{
	//alive = lives > 0;
	return alive = lives > 0;
}

void const Bunker::render() 
{
	texture->renderFrame(*rect, 0, maxLives - lives);
}

void const Bunker::save(ofstream& fil) // Guarda: tipo-posicion-vidas.
{
	fil << 4 << " " << position.getX() << " " << position.getY() << " " << lives << "\n";
}