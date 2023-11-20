#include "Mothership.h"

Mothership::Mothership(int dir) : direction(dir) {}

const int Mothership::getDirection()
{
	direction = -direction;
	return direction;
}
bool Mothership::shouldMove() 
{
	return true;
}
void Mothership::canNotMove()
{

}
const int Mothership::getAlienCount() 
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

