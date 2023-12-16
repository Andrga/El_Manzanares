#include "checkML.h"
#include "Cannon.h"
#include "Playstate.h"
#include "SDLApplication.h"


Cannon::Cannon(PlayState* gam, Point2D<double> pos, const Texture* tex, int liv, int eTime)
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), lives(liv), elapsedTime(eTime)
{

}

Cannon::~Cannon() {}

void Cannon::handleEvents(SDL_Event event)
{
	//cout << "Cannon: tu puta madre iteradores de los cojones." << endl;
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT: // Cambio de direccion a la derecha
			direction = 1;
			break;
		case SDLK_LEFT: // Cambio de direccion a la izquierda.
			direction = -1;
			break;
		case SDLK_SPACE: // Disparo.
			if (elapsedTime <= 0)
			{
				//cout << "Cannon: pium pium" << endl;
				playST->fireLaser(position, 'c');
				elapsedTime = TIEMPODISPARO;
			}
			break;
		default:
			direction = 0;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) // Cuando no hay ninguna tecla pulsada.
	{
		direction = 0;
	}
}

bool Cannon::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity) // Comprueba que el puntero al rect no sea igual a si mismo (para que un laser no colisione consigo mismo) y que no colisiones con una entidad igual (para los aliens)
	{
		if (SDL_HasIntersection(&rect, &_rect))
		{
			if (!invincible)
			{
				lives--;
				//cout << "Cannon lives: " << lives << endl;
				if (lives <= 0)
				{
					playST->gameOver();
				}
			}
			return true;
		}
	}
	return false;
};

void Cannon::update()
{
	position = position + Vector2D(velocidadCannon * direction, 0.0); // Movimiento

	// Actualiza posicion del rect.
	rect.x = position.getX();
	rect.y = position.getY();

	// Para cuando choca con un borde:
	if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()))
	{
		position = Vector2D(SCRWIDTH - texture->getFrameWidth(), position.getY());
	}
	else if (position.getX() <= 0)
	{
		position = Vector2D(0.0, position.getY());
	}


	elapsedTime--;

	// Contador de la invencibilidad.
	if (invincible)
	{
		if (timer >= maxTimer)
		{
			invincible = false;
			timer = 0;
		}
		timer++;
	}

}

void Cannon::render() const
{

	if (invincible) // Cuando la nave es invencible.
	{
		texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
	}
	else // Nave normal.
	{
		texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 2);
	}

}

void Cannon::save(ostream& fil) const // Guarda: tipo-posicion-vidas-tiempoParaDisparar.
{
	fil << 0 << " " << position.getX() << " " << position.getY() << " " << lives << " " << elapsedTime << "\n";
}

void Cannon::setInvincible()
{
	invincible = true;
}

