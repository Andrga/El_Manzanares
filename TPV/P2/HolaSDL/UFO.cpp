#include "UFO.h"
#include "Game.h"

UFO::UFO(Game* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime)
	:SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), elapsedTime(eTime)
{
	switch (sta) // Setear los diferentes estados en los que puede entrar el UFO y las posiciones iniciales.
	{
	case 0: // Entrada oculto.
		UFOstate = OCULTO;
		posInicial = pos; // Guardamos la posicion inical para cuando lo reseteemos.
		break;
	case 1: // Entrada visible.
		UFOstate = VISIBLE;
		posInicial = Point2D<double>(800, pos.getY()); // Si entra visible no nos vale la posicion que nos llega entonces la ponemos manualmente.
		break;
	case 2: // Entrada destruido.
		UFOstate = DESTRUIDO;
		posInicial = Point2D<double>(800, pos.getY()); // Si entra destruido no nos vale la posicion que nos llega entonces la ponemos manualmente.
		break;
	default:
		break;
	}
	aprearanceTime = game->getRandomRange(100, 500);
	cout << "UFO: estado inicial: " << UFOstate << endl;
}

UFO::~UFO() {}

void UFO::update()
{
	//cout << "UFO: aTime:  " << aprearanceTime << endl;
	//cout << "UFO: eTime:  " << elapsedTime << endl;
	if (UFOstate == VISIBLE)
	{
		position = position + Vector2D(-1.5, 0.0); // Movimiento.

		if (position.getX() <= -texture->getFrameWidth()) // Si pasa por el limite izquierdo.
		{
			cout << "UFO: ahora deberia de pasar a estar oculto porque se ha ido de limites." << endl;
			reset(); // Reseteo.
		}
	}
	else if (UFOstate == DESTRUIDO)
	{
		cout << "UFO: ahora deberia de hacer animacion de destruirse y reseterarse." << endl;

		if (timer >= maxTimer)
		{
			timer = 0;
			reset();
		}
		timer++;
	}
	else if (UFOstate == OCULTO && elapsedTime >= aprearanceTime)
	{
		UFOstate = VISIBLE; // Si ha pasado el tiempo de espera se vuelve visible.

		cout << "UFO: ahora deberia pasar a visible" << endl;
	}
	elapsedTime++;
}

void const UFO::render()
{
	rect->x = position.getX();
	rect->y = position.getY();

	if (UFOstate == VISIBLE)
	{
		texture->renderFrame(*rect, texture->getNumRows() - 1, texture->getNumColumns() - 2);
	}
	else if (UFOstate == DESTRUIDO)
	{
		texture->renderFrame(*rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
	}
}

void const UFO::save(ofstream& fil) // Guarda: tipo-posicion-estado-tiempoParaAparecer.
{
	fil << 5 << " " << position.getX() << " " << position.getY() << "  " << UFOstate << " " << elapsedTime << "\n";
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
		cout << "UFO: reset (des/vis)." << endl;
		UFOstate = OCULTO;
		position = posInicial;
		elapsedTime = 0;
		aprearanceTime = game->getRandomRange(500, 1000); // Reinicimaos el tiempo para la siguiente espera.
	}
	else if (UFOstate == OCULTO)
	{
		cout << "UFO: reset (ocu)." << endl;
		UFOstate = VISIBLE;
	}
}


