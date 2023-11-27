#include "Laser.h"
#include"Game.h"

Laser::Laser(Game* gam, Point2D<double> pos, const Texture* tex, char ent, Vector2D<double> vel)
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), entity(ent), velocidad(vel)
{

}
Laser::~Laser(){}
bool Laser::update() 
{
	//cout << "Laser: " << position.getX() << " " << position.getY() << endl;
	// Cambio de posición y direccion.
	if (entity == 'a') // Disparo de Alien.
	{
		position = position + velocidad;
	}
	else if (entity== 'c') // Disparo de cannon.
	{
		position = position - velocidad;
	}

	//game->colDetection(this);

	if (position.getY() <= 0 || position.getY() >= SCRHEIGHT)	//Salida de limites de la bala.
	{
		//game->hasDied(ownIte);
		alive = false;
	}
	if (game->damage(rect, entity)) 
	{
		//game->hasDied(ownIte);
		alive = false;
		
	}

	return alive;
}
void const Laser::render() 
{
	rect->x = position.getX() + (15); // +15 para que aparezca en el centro de la nave.
	rect->y = position.getY();

	texture->renderFrame(*rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

bool Laser::hit(SDL_Rect* _rect, char c)
{

	if (_rect != rect && c != entity && SDL_HasIntersection(rect, _rect))
	{
		//cout << "Laser: COLISIOOOOOOOOOON" << endl;
		//game->hasDied(ownIte);
		alive = false;
		return true;
	}
	return false;
}
