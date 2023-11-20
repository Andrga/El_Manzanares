#include "Mothership.h"

Mothership::Mothership(int dir) : direction(dir) {}

int Mothership::getDirection() const
{
	return direction;
}
bool Mothership::shouldMove() 
{
	return true;
}
void Mothership::canNotMove()
{
	direction = -direction;
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

