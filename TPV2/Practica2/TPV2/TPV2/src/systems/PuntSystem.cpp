#include "PuntSystem.h"

PuntSystem::PuntSystem()
{

}

PuntSystem::~PuntSystem()
{

}

void PuntSystem::initSystem()
{

}

void PuntSystem::update()
{
	
}

void PuntSystem::addPoints(uint8_t p)
{
	points_ += p;
	Message m;
	//m.id
}

void PuntSystem::resetPoints()
{
	points_ = 0;
}

void PuntSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_FRUIT_EAT:
		//addPoints(MIRACLE_POINTS);
		break;
	case _m_IMMUNITY_START:
		//addPoints(GHOST_POINTS);
		break;
	case _m_GHOST_EAT:
		//addPoints(FRUIT_POINTS);
		break;
	default:
		break;
	}
}