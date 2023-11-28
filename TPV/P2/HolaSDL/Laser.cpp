#include "Laser.h"
#include"Game.h"

Laser::Laser(Game* gam, Point2D<double> pos, const Texture* tex, char ent, Vector2D<double> vel)
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), entity(ent), velocidad(vel)
{

}

Laser::~Laser(){}

void Laser::update() 
{
	//cout << "Laser: " << position.getX() << " " << position.getY() << endl;
	// Cambio de posicion y direccion.
	if (entity == 'a') // Disparo de Alien.
	{
		position = position + velocidad;
	}
	else if (entity== 'c') // Disparo de cannon.
	{
		position = position - velocidad;
	}

	//Salida de limites de la bala.
	if (position.getY() <= 0 || position.getY() >= SCRHEIGHT-10) game->hasDied(ownIte);
	//Comprueba si la bala choca.
	if (game->damage(rect, entity)) game->hasDied(ownIte);
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
		//cout << "Laser: COLISIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOON" << endl;
		//game->hasDied(ownIte);
		return true;
	}
	return false;
}

void const Laser::save(ofstream& fil) // Guarda: tipo-posicion-quienHaDisparado.
{
	fil << 6 << " " << position.getX() << " " << position.getY() << " " << entity << "\n";
}