#include "Mothership.h"

Mothership::Mothership(int dir) : direction(dir) {}
const int Mothership::getDirection()
{
	direction = -direction;
	return direction;
}
bool Mothership::shouldMove() 
{

}
void Mothership::canNotMove()
{

}
const int Mothership::getAlienCount() 
{

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

