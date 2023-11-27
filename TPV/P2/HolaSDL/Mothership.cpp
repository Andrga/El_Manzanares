#include "Mothership.h"

Mothership::Mothership(int dir) : direction(dir) {}

bool Mothership::shouldMove()
{
	if (true)
	{
		return true;
	}
}
void Mothership::canNotMove()
{
	direction = -direction;
	/*for (const auto e : aliens)
	{
		e->bajar();
	}*/
}
int Mothership::getAlienCount() const
{
	return 8;
}
void Mothership::alienDied()
{
	nAliens--;
}
void Mothership::alienLanded()
{

}
void Mothership::haveLanded()
{

}
void Mothership::update()
{

}

void const Mothership::render() 
{

}

void const Mothership::save(ofstream& fil) // Guarda: tipo-nAliens.
{
	fil << 3 << " " << nAliens << "\n";
}
void Mothership::setAlienCount(int _nAliens)
{
	nAliens = _nAliens;
}

