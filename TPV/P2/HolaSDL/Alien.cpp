#include "Alien.h"
#include "checkML.h"
#include "Alien.h"
#include "Game.h"

// Constructora
Alien::Alien(const Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot)
	: subtipo(sub), SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), mothership(mot)
{
}

Alien::~Alien() {} // Destructora.

bool Alien::update() 
{
	// Movimiento del alien.
	position = position + Vector2D<double>((mothership->getDirection() * velocidadAlien), 0); // Actualizacion del movimiento y direccion.
	rect.y = position.getY();
	rect.x = position.getX();

	// Choque con un borde.
	if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()) || position.getX() <= 0)
	{
		mothership->canNotMove(); // Cuando choca con los bordes de la pantalla.
	}
	return alive;
}

const void Alien::render()
{
	//animation();

	texture->renderFrame(rect, subtipo, renderFrame);
	rect.y = position.getY();
	rect.x = position.getX();
}

void Alien::hit(SDL_Rect rect, char c)
{

}

void Alien::animation()
{
	/*if (elapsedTime <= 0)
	{
		elapsedTime = changeSprTime;
		renderFrame == 0 ? renderFrame = 1 : renderFrame = 0;
	}
	else
	{
		elapsedTime--;
	}*/
}