#include "Alien.h"
#include "Game.h"

Alien::Alien() {}
Alien::Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg)
	: posicion(pos), subtipo(subt), textura(&tex), juego(&jueg) {}

Alien::~Alien() {
	/*delete& posicion;
	delete& subtipo;
	delete textura;
	//delete& renderFrame;*/
}
void Alien::render()
{
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	textura->renderFrame(rect, subtipo, renderFrame);
}
void Alien::hit()
{
	hitted = true;
}

bool Alien::update()
{
	double xpos = juego->getDirection() * velocidadAlien; // Actualiza la direccion. 
	posicion = posicion + Vector2D<double>(xpos, 0.0); // Movimiento.

	if (posicion.getX() >= (SCRWIDTH - textura->getFrameWidth()) || posicion.getX() <= 0)
	{
		juego->cannotMove(); // Cuando choca con los bordes de la pantalla.
		//posicion = posicion + Vector2D<double>(0.0, textura->getFrameHeight() / 2);
	}

	//devuelve false si no sigue vivo
	return !hitted;

}
void Alien::animation()
{
	if (renderFrame == 0)
	{
		renderFrame = 1;
	}
	else
	{
		renderFrame = 0;
	}
}
void Alien::bajar()
{
	posicion = posicion + Vector2D<double>(0.0, textura->getFrameHeight() / 2);
}
//return el rect del alien
SDL_Rect Alien::getRect() {
	return rect;
}

