#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend)
	:posicion(pos), velocidad(vel), alien(al), game(jueg), renderer(rend)
{
	//asignamos los valores del rect aqui para no hacerlo cada iteración del bucle principal
	rect.w = 3;
	rect.h = 12;
}

Laser::~Laser() {
	//delete& posicion;
	//delete& velocidad;
	//delete& alien;
}
void Laser::render()
{
	//+15 para que aparezca en el centro de la nave
	rect.x = posicion.getX() + (15);
	rect.y = posicion.getY();

	//cout << "renderiza el disparo";

	SDL_RenderFillRect(renderer, &rect);
}
bool Laser::update() {
	alien ? posicion = posicion + velocidad : posicion = posicion - velocidad;
	game->colDetection(this);
	//hitted ? cout << "true" : cout << "false";
	if (posicion.getY() <= 0 || posicion.getY()>= SCRHEIGHT)
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
	//cout << "destruido" << endl;
}

//return true si es un cannon
bool Laser::cannon() {
	return !alien;
}
