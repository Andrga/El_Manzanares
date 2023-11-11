#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend)
	:posicion(pos), velocidad(vel), alien(al), game(jueg), renderer(rend) {}

Laser::~Laser() {
	//delete& posicion;
	//delete& velocidad;
	//delete& alien;
}
void Laser::render() 
{
	rect.x = posicion.getX()+(15);
	rect.y = posicion.getY();
	rect.w = 3;
	rect.h = 12;

	//cout << "renderiza el disparo";

	SDL_RenderFillRect(renderer, &rect);
}
bool Laser::update() {
	alien? posicion = posicion + velocidad : posicion = posicion - velocidad;
	game->colDetection(this);
	if (posicion.getY()<=0)
	{
		return false;
	}
	return !hitted;
}
//return el rect del laser
SDL_Rect Laser::getRect() {
	return rect;
}

//es llamado cuando colisiona
void Laser::hit() {
	hitted = true;
}

bool Laser::canon() {
	return alien;
}
