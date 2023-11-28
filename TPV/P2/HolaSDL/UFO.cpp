#include "UFO.h"
#include "Game.h"

UFO::UFO(Game* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime)
	:SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), elapsedTime(eTime)
{
	UFOstate = static_cast<states>(sta); // Convertimos lo que nos llega de archivo al state correspondiente.
	//posInicial = pos; // Guardamos la poscion inical para cuando lo reseteamos.
}

UFO::~UFO() {}

void UFO::update()
{
	aprearanceTime = game->getRandomRange(0, TIEMPOAPARICION);

	if (UFOstate == VISIBLE)
	{
		position = position + Vector2D(1.1 * 1, 0.0); // Movimiento
		if (position.getX() <= 0)
		{
			UFOstate = OCULTO;
		}
	}
	else if (UFOstate == DESTRUIDO)
	{
		//animacion();
		reset();
	}
	else if (UFOstate == OCULTO && elapsedTime >= aprearanceTime)
	{
		elapsedTime = 0;
		UFOstate = VISIBLE; // Si ha pasado el tiempo de espera se vuelve visible.
		aprearanceTime = game->getRandomRange(0, TIEMPOAPARICION); // Reinicimaos el tiempo para la siguiente espera.
	}
	elapsedTime++;
}

void const UFO::render()
{
	rect->x = position.getX();
	rect->y = position.getY();
	texture->renderFrame(*rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

void const UFO::save(ofstream& fil)
{

}

bool UFO::hit(SDL_Rect* _rect, char c)
{
	if (_rect != rect && c != entity)
	{
		if (SDL_HasIntersection(rect, _rect))
		{
			UFOstate = DESTRUIDO;
			cout << "UFO: hit" << endl;
			//game->hasDied(ownIte); // Suponemos que no se elimina aunque lo eliminemos y lo que se hace es transportalo a la posicion de inicio.
			return true;
		}
	}
	return false;
}

void UFO::reset() 
{
	if (UFOstate == DESTRUIDO || UFOstate == VISIBLE)
	{
		UFOstate = OCULTO;
		//position = posInicial;
	}
}
