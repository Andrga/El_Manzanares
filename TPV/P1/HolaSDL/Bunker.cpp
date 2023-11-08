#include "Bunker.h"

Bunker::Bunker(Point2D<double> pos, int vid, Texture& tex)
	: posicion(pos), vidas(vid), textura(&tex){}
Bunker::~Bunker() {
	//delete &posicion;
	//delete &vidas;
	delete textura;
}

void Bunker::render()
{
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	textura->renderFrame(rect, 0, 0);

};
bool Bunker::update() // Update.
{
	return true;
};
void Bunker::hit()
{
	vidas--;
	// Renderizar apariencia nueva
};
