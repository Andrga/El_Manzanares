#include "Alien.h"
#include "checkML.h"
#include "Alien.h"
#include "Game.h"

// Constructora
Alien::Alien(const Game* gam,Point2D<int> pos, int sub, const Texture* tex, Mothership* mot)
	: subtipo(sub), SceneObject(gam, pos, tex), mothership(mot)
{
	//rect.w = texture->getFrameWidth();
	//rect.h = texture->getFrameHeight();
}

Alien::~Alien() {} // Destructora.

bool Alien::update() 
{
	// Movimiento del alien.
	position = position + Vector2D<int>((mothership->getDirection() * velocidadAlien), 0); // Actualizacion del movimiento y direccion.

	// Choque con un borde.
	if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()) || position.getX() <= 0)
	{
		mothership->canNotMove(); // Cuando choca con los bordes de la pantalla.
	}
	return alive;
}

const void Alien::render()
{
	animation();

	rect.x = position.getX();
	rect.y = position.getY();
	texture->renderFrame(rect, subtipo, renderFrame);

}

void Alien::hit(SDL_Rect rect, char c)
{

}

void Alien::animation()
{
	if (elapsedTime <= 0)
	{
		elapsedTime = changeSprTime;
		renderFrame == 0 ? renderFrame = 1 : renderFrame = 0;
	}
	else
	{
		elapsedTime--;
	}
}