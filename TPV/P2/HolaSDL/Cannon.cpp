#include "Cannon.h"


Cannon::Cannon(Game* gam, Point2D<double> pos, const Texture* tex, int liv, int eTime)
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
			//if (elapsedTime >= TIEMPODISPARO)
			//{
				//cout << "Cannon: pium pium" << endl;
			game->fireLaser(position, 'c');
			elapsedTime = 0;
			//}
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

bool Cannon::hit(SDL_Rect* _rect, char c)
{
	//cout << "Alien: hit" << endl;
	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			cout << "Cannon: hit." << endl;
			//game->hasDied(ownIte);
			lives--;
			cout << "Cannon lives: " << lives << endl;
			if (!(lives <= 0))
			{
				game->gameOver();
			}
			return true;
		}
	}
	return false;
}

void Cannon::update()
{
	position = position + Vector2D(velocidadCannon * direction, 0.0); // Movimiento

	// Para cuando choca con un borde:
	if (position.getX() >= (SCRWIDTH - texture->getFrameWidth()))
	{
		position = Vector2D(SCRWIDTH - texture->getFrameWidth(), position.getY());
	}
	else if (position.getX() <= 0)
	{
		position = Vector2D(0.0, position.getY());
	}

	elapsedTime++;

}

void const Cannon::render()
{
 	rect->x = position.getX();
	rect->y = position.getY();
	texture->renderFrame(*rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

void const Cannon::save(ofstream& fil) // Guarda: tipo-posicion-vidas-tiempoParaDisparar.
{
	fil << 0 << " " << position.getX() << " " << position.getY() << " " << lives << " " << elapsedTime << "\n";
}

