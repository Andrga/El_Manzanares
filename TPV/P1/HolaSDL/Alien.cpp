#include "checkML.h"
#include "Alien.h"
#include "Game.h"

// Constructora
Alien::Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg)
	: posicion(pos), subtipo(subt), textura(&tex), juego(&jueg)
{
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	elapsedShootTime = juego->getRandomRange(minShootTime, maxShootTime);
}

// Destructora
Alien::~Alien() {
	/*delete& posicion;
	delete& subtipo;
	delete textura;
	//delete& renderFrame;*/
}

// Render
void Alien::render()
{
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	textura->renderFrame(rect, subtipo, renderFrame);
}

// Hit
void Alien::hit()
{
	hitted = true;
}

// Update
bool Alien::update()
{
	//movimiento del alien
	posicion = posicion + Vector2D<double>(juego->getDirection() * velocidadAlien, 0.0); // Actualización del movimiento y direccion.

	//choque con un borde
	if (posicion.getX() >= (SCRWIDTH - textura->getFrameWidth()) || posicion.getX() <= 0)
	{
		juego->cannotMove(); // Cuando choca con los bordes de la pantalla.
	}

	//contador para disparar los aliens
	if (subtipo == 0)
	{
		if (elapsedShootTime <= 0)
		{
			juego->fireLaser(posicion, true);
			// aliens disparan en un tiempo aleatorio
			elapsedShootTime = juego->getRandomRange(minShootTime, maxShootTime);
		}
		else
		{
			elapsedShootTime--;
		}
	}
	//devuelve false si no sigue vivo
	return !hitted;

}
//cambia el frarme de la animación
void Alien::animation()
{
	renderFrame == 0 ? renderFrame = 1 : renderFrame = 0;
}

//Baja a el alien
void Alien::bajar()
{
	posicion = posicion + Vector2D<double>(0.0, textura->getFrameHeight() / 2);
}

//return el rect del alien
SDL_Rect Alien::getRect() {
	return rect;
}

