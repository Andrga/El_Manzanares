#include "Laser.h"

Laser::Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend)
	:posicion(pos), velocidad(vel), alien(al), game(jueg), renderer(rend) {}

Laser::~Laser() {
	//delete& posicion;
	//delete& velocidad;
	//delete& alien;
}
void Laser::render() 
{
	rectangulo.x = posicion.getX()+(15);
	rectangulo.y = posicion.getY();
	rectangulo.w = 3;
	rectangulo.h = 12;

	//cout << "renderiza el disparo";

	SDL_RenderFillRect(renderer, &rectangulo);
}
bool Laser::update() {
	posicion = posicion - velocidad;
	//game->collisionD
	return true;
}
