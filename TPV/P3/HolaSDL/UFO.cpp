#include "UFO.h"
#include "PlayState.h"

UFO::UFO(PlayState* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime)
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
	aprearanceTime = playST->getRandomRange(100, 500);
	//cout << "UFO: pos inicial: " << posInicial.getX() << endl;
}

//UFO::~UFO() {}

void UFO::update()
{
	//cout << "UFO: pos inicial: " << posInicial.getX() << " UFO: pos : " << position.getX() << endl;

	//cout << "UFO: aTime:  " << aprearanceTime << endl;
	//cout << "UFO: eTime:  " << elapsedTime << endl;
	if (UFOstate == VISIBLE)
	{
		position = position + Vector2D(-5.0, 0.0); // Movimiento.
		//position = position + Vector2D(-0.25, 0.0); // Para probar cosas del UFO y no vaya muy rapido >:(


		if (position.getX() <= -texture->getFrameWidth()) // Si pasa por el limite izquierdo se resetea para que vuelva a su poscion inicial.
		{
			//cout << "UFO: ahora deberia de pasar a estar oculto porque se ha ido de limites." << endl;
			reset(); // Reseteo.
		}

		// Update rect.
		rect.x = position.getX();
		rect.y = position.getY();
	}
	else if (UFOstate == DESTRUIDO)
	{
		//cout << "UFO: ahora deberia de hacer animacion de destruirse y resetearse." << endl;
		// Rewards y bombas:
		if (playST->getRandomRange(0, MAX_APPEARANCE_PERCENTAJE) < proporcionBombas && !reward) {
			reward = true;
			playST->fireBomb(position);
		}
		else if (playST->getRandomRange(0, MAX_APPEARANCE_PERCENTAJE) > proporcionBombas && !reward) {
			reward = true;
			playST->fireReward(position);
		}
		if (timer >= maxTimer) // Timer para que el sprite del UFO destruido se quede en pantalla un poco.
		{
			timer = 0;
			reset();
		}
		timer++;
	}
	else if (UFOstate == OCULTO && elapsedTime >= aprearanceTime)
	{
		UFOstate = VISIBLE; // Si ha pasado el tiempo de espera se vuelve visible.
		//cout << "UFO: ahora deberia pasar a visible" << endl;
	}
	elapsedTime++;
}

void UFO::render() const
{

	if (UFOstate == VISIBLE) // textura del UFO cuando pasa por la pantalla.
	{
		texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 2);
	}
	else if (UFOstate == DESTRUIDO) // Si el UFO ha sido destruido le ponemos la textura que corresponde.
	{
		texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
	}
}

void UFO::save(std::ostream& fil) const // Guarda: tipo-posicion-estado-tiempoParaAparecer.
{
	fil << 5 << " " << position.getX() << " " << position.getY() << "  " << UFOstate << " " << elapsedTime << "\n";
}

bool UFO::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity) // Comprueba que el puntero al rect no sea igual a si mismo (para que un laser no colisione consigo mismo) y que no colisiones con una entidad igual (para los aliens).
	{
		if (SDL_HasIntersection(&rect, &_rect))
		{
			UFOstate = DESTRUIDO; // Si ha sido alcanzado se cambia al estado de Destruido.
			//cout << "UFO: hit" << endl;
			//game->hasDied(ownIte); // Suponemos que no se elimina aunque lo eliminemos y lo que se hace es transportalo a la posicion de inicio.
			playST->addScore(100);
			//playST->invencible(); // Al destruirse el UFO la nave se hace invencible durante un tiempo.
			return true;
		}
	}
	return false;
}

void UFO::reset() // Pone el estado del UFO que le corresponde y modifica el eTime y la posicion de este.
{
	if (UFOstate == DESTRUIDO || UFOstate == VISIBLE)
	{
		//cout << "UFO: reset (des/vis)." << endl;
		//cout << "UFO: pos inicial: " << posInicial.getX() << " UFO: pos : " << position.getX() << endl;
		reward = false;
		UFOstate = OCULTO;
		position = posInicial;
		rect.x = posInicial.getX();
		elapsedTime = 0;
		aprearanceTime = playST->getRandomRange(500, 1000); // Reiniciamos el tiempo para la siguiente espera.
	}
	else if (UFOstate == OCULTO)
	{
		//cout << "UFO: reset (ocu)." << endl;
		UFOstate = VISIBLE;
	}
}


