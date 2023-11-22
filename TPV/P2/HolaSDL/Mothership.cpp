#include "Mothership.h"

Mothership::Mothership(int dir, int nAl) : direction(dir), nAliens(nAl) {}

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

}
void Mothership::alienLanded()
{

}
void Mothership::haveLanded()
{

}
bool Mothership::update() 
{
	return true;
}
void const Mothership::render() 
{

}

