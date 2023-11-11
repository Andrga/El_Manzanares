#include "Cannon.h"
#include "Game.h"

Cannon::Cannon(Point2D<double> pos, Texture& tex, int vid, Game& gam)
	:posicion(pos), textura(&tex), vidas(vid), game(&gam)
{}
Cannon::~Cannon() {
	//delete& posicion;
	delete textura;
	//delete& direccion;
	//delete& vidas;
}
void Cannon::render() {
	rect.x = posicion.getX();
	rect.y = posicion.getY();
	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);

}

bool Cannon::hit()
{
	return false;
}

bool Cannon::update()
{
	posicion = posicion + Vector2D(velocidadCannon * direccion, 0.0); // Movimiento
	// Para cuando choca con un borde:
	if (posicion.getX() >= (SCRWIDTH - textura->getFrameWidth()))
	{
		posicion = Vector2D(SCRWIDTH - textura->getFrameWidth(), posicion.getY());
	}
	else if (posicion.getX() <= 0)
	{
		posicion = Vector2D(0.0, posicion.getY());
	}
	elapsedTime++;
	return !hit();
}

void Cannon::handleEvent(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		//int key = SDL_GetKeyboardState(3);
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT: // Cambio de direccion a la derecha
			direccion = 1;
			break;
		case SDLK_LEFT: // Cambio de direccion a la izquierda.
			//std::cout << "Izquierda\n";
			direccion = -1;
			break;
		case SDLK_SPACE: // Cambio de direccion a la izquierda.
			if (elapsedTime >= TIEMPODISPARO)
			{
				//std::cout << "Disparo\n";
				game->fireLaser(posicion, false);
				elapsedTime = 0;
			}
			/*else {
				std::cout << elapsedTime;
			}*/
			break;
		default:
			direccion = 0;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) // Cuando no hay ninguna tecla pulsada.
	{
		direccion = 0;
	}
}
//return el rect del Cannon
SDL_Rect Cannon::getRect() {
	return rect;
}