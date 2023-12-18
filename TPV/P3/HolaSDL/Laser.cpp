#include "checkML.h"
#include "Laser.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "SDL.h"


Laser::Laser(PlayState* playST, Point2D<double> pos, char ent, Vector2D<double> vel, SDL_Renderer* _renderer)
	: SceneObject(playST, pos, 3, 21,nullptr), entity(ent), velocidad(vel), renderer(_renderer)
{
	if (entity == 'c')
	{
		color.r = 255;
		color.g = 87;
		color.b = 51;
	}
	else
	{
		color.r = 53;
		color.g = 255;
		color.b = 255;
	}
}

Laser::~Laser(){}

void Laser::update() 
{
	if (entity == 'a') // Disparo de Alien.
	{
		position = position + velocidad;
	}
	else if (entity== 'c') // Disparo de cannon.
	{
		position = position - velocidad;
	}
	// Actualizacion del rect.
	rect.x = position.getX();
	rect.y = position.getY();

	//Salida de limites de la bala.
	if (position.getY() <= 0 || position.getY() >= SCRHEIGHT-10) playST->hasDied(scAnch);
	//Comprueba si la bala choca.
	if (playST->damage(rect, entity)) playST->hasDied(scAnch);

}

void Laser::render() const
{
	renderRect();
}

void Laser::renderRect() const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

bool Laser::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity && SDL_HasIntersection(&rect, &_rect))
	{
		return true;
	}
	return false;
}

void Laser::save(ostream& fil) const // Guarda: tipo-posicion-quienHaDisparado.
{
	fil << 6 << " " << position.getX() << " " << position.getY() << " " << entity << "\n";
}