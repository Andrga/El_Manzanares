#include "Alien.h"
#include "Game.h"

//constructor predeterminado
Alien::Alien()
{
	//Alien(Point2D<double>(0, 0), 0, new Texture, new Game);
}

//constructora
Alien::Alien(Point2D<double> pos, int subt, Texture& tex, Game& jueg)
	: posicion(pos), subtipo(subt), textura(&tex), juego(&jueg)
{
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	elapsedShootTime = juego->getRandomRange(minShootTime, maxShootTime);
}

//destructora
Alien::~Alien() {
	/*delete& posicion;
	delete& subtipo;
	delete textura;
	//delete& renderFrame;*/
}

//render
void Alien::render()
{
	//cout << "yipi" << endl;
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	textura->renderFrame(rect, subtipo, renderFrame);
}

//hit
void Alien::hit()
{
	hitted = true;
}

//update
bool Alien::update()
{
	//movimiento del alien
	double xpos = juego->getDirection() * velocidadAlien; // Actualiza la direccion. 
	posicion = posicion + Vector2D<double>(xpos, 0.0); // Movimiento.

	//choque con un borde
	if (posicion.getX() >= (SCRWIDTH - textura->getFrameWidth()) || posicion.getX() <= 0)
	{
		juego->cannotMove(); // Cuando choca con los bordes de la pantalla.
		//posicion = posicion + Vector2D<double>(0.0, textura->getFrameHeight() / 2);
	}

	//contador para disparar los aliens
	if (subtipo == 0)
	{
		if (elapsedShootTime <= 0)
		{
			juego->fireLaser(posicion, true);
			elapsedShootTime = juego->getRandomRange(minShootTime, maxShootTime);
			//cout << "dispara alien" << endl;
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
	/*if (renderFrame == 0)
	{
		renderFrame = 1;
	}
	else
	{
		renderFrame = 0;
	}*/
}
void Alien::bajar()
{
	posicion = posicion + Vector2D<double>(0.0, textura->getFrameHeight() / 2);
}
//return el rect del alien
SDL_Rect Alien::getRect() {
	return rect;
}

