#include "Alien.h"
#include "checkML.h"
#include "Game.h"

// Constructora
Alien::Alien(Game* gam, Point2D<double> pos, int sub, const Texture* tex, Mothership* mot)
	: subtipo(sub), SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), mothership(mot)
{
	posYAnt = pos.getY();
}

Alien::~Alien() {} // Destructora.

void Alien::update()
{
	move = mothership->shouldMove();
	//cout << move << "Move" << endl;
	if (move)
	{
		animation();
		// Movimiento del alien.

		position = Vector2D<double>((position.getX() + (mothership->getDirection() * velocidadAlien )), posYAnt + mothership->getLevel()*20); // Actualizacion del movimiento y direccion.

		// Actualizacion de la posicion del rect.
		rect->y = position.getY();
		rect->x = position.getX();

		// Choque con un borde.
		if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()) || position.getX() <= 0)
		{
			mothership->canNotMove(); // Cuando choca con los bordes de la pantalla.
		}

		// Comprueba si ha landeado.
		if (position.getY() >= game->getCannonYPos())
		{
			mothership->alienLanded();
		}
	}
}

const void Alien::render()
{
	texture->renderFrame(*rect, subtipo, renderFrame);
}

bool Alien::hit(SDL_Rect* _rect, char c)
{
	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			//cout << "Alien: hit" << endl;
			switch (subtipo)
			{
			case 0:
				game->addScore(30);
				break;
			case 1:
				game->addScore(20);
				break;
			case 2:
				game->addScore(10);
				break;
			default:
				break;
			}
			game->hasDied(ownIte);
			mothership->alienDied();
			return true;
		}
	}
	return false;
}

void Alien::bajar() 
{
	position = position + Vector2D<double>(0.0, (mothership->getLevel() * 10)); // Actualizacion del movimiento y direccion.
}


void const Alien::save(ofstream& fil) // Guarda: tipo-posicion-subtipo.
{
	fil << 1 << " " << position.getX() << " " << position.getY() << " " << subtipo << " " << "\n";
}