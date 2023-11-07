#include "Laser.h"

Laser::Laser(Point2D<double> pos, Vector2D<double> vel, bool al) :posicion(pos), velocidad(vel), alien(al) {}

Laser::~Laser() {
	delete& posicion;
	delete& velocidad;
	delete& alien;
}
void Laser::render() {

}
bool Laser::update() {
	posicion = posicion + velocidad;
	return true;
}
