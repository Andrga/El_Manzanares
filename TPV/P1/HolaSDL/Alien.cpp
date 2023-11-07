#include "Alien.h"
#include "Game.h"

Alien::Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg)
{
	posicion = pos;
	subtipo = subt;
	textura = &tex;
	juego = &jueg;
}
void Alien::render()
{
	SDL_Rect rect;
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	textura->renderFrame(rect, subtipo, renderFrame);
}
bool Alien::hit()
{
	return false;
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

	return !hit();
	
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

