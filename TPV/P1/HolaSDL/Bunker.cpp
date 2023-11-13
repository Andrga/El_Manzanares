#include "checkML.h"
#include "Bunker.h"

//Constructora
Bunker::Bunker(Point2D<double> pos, int vid, Texture& tex)
	: posicion(pos), maxVidas(vid), textura(&tex) 
{
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
}

//Destructora
Bunker::~Bunker() {
	//delete &posicion;
	//delete &vidas;
	//delete textura;
}

//Render
void Bunker::render()
{
	textura->renderFrame(rect, 0, actVidas);

};

// Update.
bool Bunker::update() 
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

// Es llamado cuando es golpeado por un laser
void Bunker::hit()
{
	// Renderizar apariencia nueva
	actVidas++;
};
