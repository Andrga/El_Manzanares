#include "UFO.h"

UFO::UFO(Game* gam, Point2D<double> pos, const Texture* tex, int sta, int eTime)
	:SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), _state(sta), elapsedTime(eTime)
{

}

UFO::~UFO() {}


void UFO::state()
{

}

void UFO::update() 
{

}

void const UFO::render()
{

}

void const UFO::save(ofstream& fil)
{

}
