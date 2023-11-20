#include "Alien.h"
#include "checkML.h"
#include "Alien.h"
//#include "Game.h"

// Constructora
Alien::Alien(Point2D<int> pos, int sub, const Texture& tex, const Game& gam, const Mothership& mot)
	: subtipo(sub), SceneObject(gam, pos, tex), mothership(&mot)
{
	//rect.w = texture->getFrameWidth();
	//rect.h = texture->getFrameHeight();
}

Alien::~Alien() {} // Destructora.

bool Alien::update() 
{
	return alive;
}
const void Alien::render()
{

}
void Alien::hit(SDL_Rect rect, char c)
{

}