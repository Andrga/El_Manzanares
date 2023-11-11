#include "Bunker.h"

Bunker::Bunker(Point2D<double> pos, int vid, Texture& tex)
	: posicion(pos), maxVidas(vid), textura(&tex) 
{
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
}
Bunker::~Bunker() {
	//delete &posicion;
	//delete &vidas;
	//delete textura;
}

void Bunker::render()
{
	textura->renderFrame(rect, 0, actVidas);

};
bool Bunker::update() // Update.
{
	if (actVidas >= maxVidas)
	{
		return false;
	}
	return true;
};
//return el rect del laser
SDL_Rect Bunker::getRect() {
	return rect;
}
void Bunker::hit()
{
	actVidas++;
	// Renderizar apariencia nueva
	std::cout << "kerokekambie el frame plis";
};
