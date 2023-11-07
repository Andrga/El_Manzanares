#include "Bunker.h"

Bunker::Bunker(Point2D<double> pos, int vid, Texture& tex)
	: posicion(pos), vidas(vid), textura(&tex){}

void Bunker::render()
{
	SDL_Rect rect;
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	textura->renderFrame(rect, 0, 0);

};
bool Bunker::update() // Update.
{
	if (vidas > 0)
	{
		return true;
	}
	else return false;
};
void Bunker::hit()
{
	vidas--;
	// Renderizar apariencia nueva
};
