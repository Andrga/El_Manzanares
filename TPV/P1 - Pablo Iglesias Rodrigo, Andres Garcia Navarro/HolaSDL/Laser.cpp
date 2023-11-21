#include "checkML.h"
#include "Laser.h"
#include "Game.h"

// Constructora
Laser::Laser(Point2D<double> pos, Vector2D<double> vel, bool al, Game* jueg, SDL_Renderer* rend)
	:posicion(pos), velocidad(vel), alien(al), game(jueg), renderer(rend)
{
	//asignamos los valores del rect aqui para no hacerlo cada iteración del bucle principal
	rect.w = 3;
	rect.h = 12;
}

// Destructora
Laser::~Laser() {
}

//Renderizado del laser
void Laser::render()
{
	//+15 para que aparezca en el centro de la nave
	rect.x = posicion.getX() + (15);
	rect.y = posicion.getY();

	SDL_RenderFillRect(renderer, &rect);
}

//Update del laser
bool Laser::update() {
	//Cambio de posición y direccion
	alien ? posicion = posicion + velocidad : posicion = posicion - velocidad;
	game->colDetection(this);

	//Salida de limites de la bala
	if (posicion.getY() <= 0 || posicion.getY()>= SCRHEIGHT)
	{
		return false;
	}

	return !hitted;
}

//Return el rect del laser
SDL_Rect Laser::getRect() {
	return rect;
}

//Es llamado cuando colisiona
void Laser::hit() {
	hitted = true;
}

//Return true si es un cannon
bool Laser::cannon() {
	return !alien;
}
