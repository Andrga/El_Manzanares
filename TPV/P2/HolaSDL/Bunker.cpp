#include "Bunker.h"
#include "game.h"


Bunker::Bunker(const Game &gam, int liv, Point2D<int> pos, const Texture& tex) : SceneObject(gam, pos, tex), lives(liv)
{}
Bunker::~Bunker()
{

}
void Bunker::hit(SDL_Rect rect, char c) 
{
	lives--;
}