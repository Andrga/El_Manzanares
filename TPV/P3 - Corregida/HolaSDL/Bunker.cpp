#include "checkML.h"
#include "Bunker.h"
#include "PlayState.h"

using namespace std;

Bunker::Bunker(PlayState* gam, int liv, Point2D<double> pos, const Texture* tex)
	: SceneObject(gam, pos, tex->getFrameWidth(), tex->getFrameHeight(), tex), maxLives(liv)
{
	rect.x = position.getX();
	rect.y = position.getY();
	lives = maxLives;

}

//Bunker::~Bunker() {}

bool Bunker::hit(SDL_Rect _rect, char c)
{
	//	//lives--;
	//	alive = lives <= 0;
	//	//cout << "ay ay ay" << lives;
	//	return false;

	if ((&_rect) != (&rect) && c != entity)
	{
		if (SDL_HasIntersection(&rect, &_rect))
		{
			//cout << "Bunker: hit" << endl;
			lives--;
			if (lives <= 0)
			{
				playST->hasDied(scAnch, objAnch);
			}
			return true;
		}
	}
	return false;
}
void Bunker::update()
{
}

void Bunker::render()const
{
	texture->renderFrame(rect, 0, maxLives - lives);
}

void Bunker::save(ostream& fil) const // Guarda: tipo-posicion-vidas.
{
	fil << ID_BUNKER << " " << position.getX() << " " << position.getY() << " " << lives << "\n";
}
