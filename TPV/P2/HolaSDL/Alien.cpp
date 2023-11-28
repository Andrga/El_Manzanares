#include "Alien.h"
#include "checkML.h"
#include "Game.h"

// Constructora
Alien::Alien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot)
	: subtipo(sub), SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), mothership(mot)
{
}

Alien::~Alien() {} // Destructora.

void Alien::update() 
{
	// Movimiento del alien.
	position = position + Vector2D<double>((mothership->getDirection() * velocidadAlien), 0); // Actualizacion del movimiento y direccion.
	rect->y = position.getY();
	rect->x = position.getX();

	// Choque con un borde.
	if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()) || position.getX() <= 0)
	{
		mothership->canNotMove(); // Cuando choca con los bordes de la pantalla.
	}
	if (game->damage(rect, entity))
	{
		mothership->alienDied();
	}

}

const void Alien::render()
{
	//animation();
	rect->y = position.getY();
	rect->x = position.getX();
	texture->renderFrame(*rect, subtipo, renderFrame);
}

bool Alien::hit(SDL_Rect* _rect, char c)
{
	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			//cout << "Alien: hit" << endl;
			game->hasDied(ownIte);
			mothership->alienDied();
			return true;
		}
	}
	return false;
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

void const Alien::save(ofstream& fil) // Guarda: tipo-posicion-subtipo.
{
	fil << 1 << " " << position.getX() << " " << position.getY() << " " << subtipo << " " << "\n";
}