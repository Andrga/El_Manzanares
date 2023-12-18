#include "Shield.h"
#include "checkML.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "SceneObject.h"
#include "SDL.h"


Shield::Shield(PlayState* playST, Point2D<double> pos)
	: SceneObject(playST, pos, playST->getGame()->getTexture(SHIELD)->getFrameWidth(), playST->getGame()->getTexture(SHIELD)->getFrameHeight(), nullptr)
{
	tex = playST->getGame()->getTexture(SHIELD);
}

Shield::~Shield() {}

void Shield::update()
{
	position = position + Point2D<double>(0, velocidadBomb);
	// Actualizacion del rect.
	rect.x = position.getX();
	rect.y = position.getY();

	//Salida de limites de la bala.
	if (position.getY() <= 0 || position.getY() >= SCRHEIGHT - 10) playST->hasDied(scAnch);
	//Comprueba si la bala choca.
	/*if (playST->damage(rect, entity)) {
		vidas <= 0 ? playST->hasDied(scAnch) : vidas--;
	}*/

}

void Shield::render() const
{
	tex->render(rect);
}

bool Shield::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity && SDL_HasIntersection(&rect, &_rect))
	{
		return true;
	}
	return false;
}

void Shield::save(ostream& fil) const // Guarda: tipo-posicion-quienHaDisparado.
{
	fil << 9 << " " << position.getX() << " " << position.getY() << "\n";
}
