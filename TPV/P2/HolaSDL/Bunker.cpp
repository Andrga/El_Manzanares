#include "Bunker.h"
#include "game.h"


Bunker::Bunker(const Game *gam, int liv, Point2D<int> pos, const Texture* tex) 
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), lives(liv)
{
	rect.x = position.getX();
	rect.y = position.getY();

}
Bunker::~Bunker()
{

}
void Bunker::hit(SDL_Rect rect, char c) 
{
	lives--;
}
bool Bunker::update() 
{
	return lives >= 0; // Devuelve true si está vivo.
}
void const Bunker::render() 
{
	texture->renderFrame(rect, 0, lives);
}