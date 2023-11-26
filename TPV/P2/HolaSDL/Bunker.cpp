#include "Bunker.h"
#include "game.h"


Bunker::Bunker(Game *gam, int liv, Point2D<double> pos, const Texture* tex) 
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), maxLives(liv)
{
	rect->x = position.getX();
	rect->y = position.getY();
	lives = maxLives;

}
Bunker::~Bunker()
{

}
void Bunker::hit(SDL_Rect *rect, char c) 
{
	//lives--;
}
bool Bunker::update() 
{
	return lives >= 0; // Devuelve true si está vivo.
}
void const Bunker::render() 
{
	texture->renderFrame(*rect, 0, maxLives - lives);
}