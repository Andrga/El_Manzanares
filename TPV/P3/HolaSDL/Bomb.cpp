#include "Bomb.h"
#include "checkML.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "SceneObject.h"
#include "SDL.h"

using namespace std;

Bomb::Bomb(PlayState* playST, Point2D<double> pos, int vid)
	: SceneObject(playST, pos, playST->getGame()->getTexture(BOMB)->getFrameWidth(), playST->getGame()->getTexture(BOMB)->getFrameHeight(), nullptr), vidas(vid)
{
	tex = playST->getGame()->getTexture(BOMB);
}

//Bomb::~Bomb() {}

void Bomb::update()
{
	position = position + Point2D<double>(0, velocidadBomb);
	// Actualizacion del rect.
	rect.x = position.getX();
	rect.y = position.getY();

	//Salida de limites de la bala.
	if (position.getY() >= SCRHEIGHT - 10) playST->hasDied(scAnch, objAnch);
	//Comprueba si la bala choca.
	if (playST->damage(rect, entity)) {
		vidas <= 0 ? playST->hasDied(scAnch, objAnch) : vidas--;
	}

}

void Bomb::render() const
{
	tex->render(rect);
}

bool Bomb::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity && SDL_HasIntersection(&rect, &_rect))
	{
		return true;
	}
	return false;
}

void Bomb::save(ostream& fil) const // Guarda: tipo-posicion-quienHaDisparado.
{
	fil << 8 << " " << position.getX() << " " << position.getY() << " " << vidas << "\n";
}