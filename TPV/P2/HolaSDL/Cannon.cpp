#include "Cannon.h"

Cannon::Cannon(const Game* gam, Point2D<int> pos, const Texture* tex, int liv, int dir) 
	: SceneObject(gam, pos, tex), lives(liv), direction(dir) 
{

}

Cannon::~Cannon()
{

}

void Cannon::handleEvents(SDL_Event event)
{
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
		/*case SDLK_SPACE: // Cambio de direccion a la izquierda.
			if (elapsedTime >= TIEMPODISPARO)
			{
				game->fireLaser(position, false);
				elapsedTime = 0;
			}
			break;*/
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
void Cannon::hit(SDL_Rect rect, char c) 
{
	lives--;
}
bool Cannon::update() 
{
	return true;
}
void const Cannon::render() 
{
	
}


