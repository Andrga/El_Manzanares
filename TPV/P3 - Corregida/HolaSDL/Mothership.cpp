#include "checkML.h"
#include "Mothership.h"
#include "PlayState.h"

using namespace std;

Mothership::Mothership(PlayState* plST, SDLApplication* appl) 
	:GameObject(plST), playST(plST)
{}
bool Mothership::shouldMove()
{
	//comprueba si se puede mover el alien (se mueve tambien si esta terminando de hacer el spin)
	if (_state == MOVE || _state == SPIN)
	{
		//registra cuantos aliens han llamado al metodo
		if (aliensReistrados < nAliens)
		{
			aliensReistrados++;
		}
		else
		{
			// Una vez todos los aliens han sido registrados (es decir, ya se han movido) pasa al estado stop
			elapsedTime = maxTime - level;
			aliensReistrados = 0;
			_state = STOP;
		}
	}
	//cout << "Reg Aliens: " << aliensReistrados << endl;
	return _state == MOVE || _state == SPIN;
}
void Mothership::canNotMove()
{
	_state = SPIN;
}
int Mothership::getAlienCount() const
{
	return nAliens;
}
void Mothership::alienDied()
{
	nAliens--;
}
void Mothership::alienLanded()
{
	_state = LANDED;
}
void Mothership::haveLanded()
{
	playST->gameOver();
}
void Mothership::update()
{	
	//cout << "Start: " << _state << endl;
	switch (_state)
	{
	case Mothership::MOVE:
		break;
	case Mothership::STOP: // Lleva la cuenta atras de cuando pasar al estado MOVE.
		elapsedTime <= 0 ? _state = MOVE : elapsedTime--;
		break;
	case Mothership::SPIN:	// Cambia de direccon, va al estado STOP, y aumenta el nivel de altura.
		direction = -direction;
		_state = STOP;
		level ++;
		//velocidadAlien += level;
		break;
	case Mothership::LANDED:
		haveLanded();
		break;
	default:
		break;
	}


	//cout << "End: " << _state << endl;
	//cout << "Etime: " << elapsedTime << endl;

}

void Mothership::render() const
{}

void Mothership::save(ostream& fil) const // Guarda: tipo-nAliens.
{
	fil << "3 " << _state << " " << level << " " << elapsedTime << "\n";
}


void Mothership::setMotherParams(int sta, int lev, int esp) {
	_state = (state)sta;
	level = lev;
	elapsedTime = esp;
}

void Mothership::setAlienCount(int _nAliens)
{
	nAliens = _nAliens;
}

