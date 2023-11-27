#include "Alien.h"
#include "checkML.h"
#include "Alien.h"
#include "Game.h"

// Constructora
Alien::Alien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot, int nomb)
	: subtipo(sub), SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), mothership(mot), nombre(nomb)
{
}

Alien::~Alien() {} // Destructora.

bool Alien::update() 
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
	if (!alive)
	{
		mothership->alienDied();
	}

	return alive;
}

const void Alien::render()
{
	//animation();

	texture->renderFrame(*rect, subtipo, renderFrame);
	rect->y = position.getY();
	rect->x = position.getX();
}

bool Alien::hit(SDL_Rect* _rect, char c)
{
	//cout << "Alien: hit" << endl;
	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			//cout << "Alien: interseccion" << nombre << endl;
			//game->hasDied(ownIte);
			alive = false;
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

void const Alien::save(ofstream& fil) // Guarda: tipo-subtipo-posicion.
{
	fil << 1 << " " << subtipo << " " << position.getX() << " " << position.getY() << "\n";
}