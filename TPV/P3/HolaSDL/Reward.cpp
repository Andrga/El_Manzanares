#include "Reward.h"
#include "checkML.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "SceneObject.h"
#include "SDL.h"

Reward::Reward(PlayState* playST, Point2D<double> pos, SDLEventCallback rew, Texture* _tex)
	: SceneObject(playST, pos, _tex->getFrameWidth(), _tex->getFrameHeight(), nullptr), rewardCallback(rew), tex(_tex)
{}

//Reward::~Reward() {}

void Reward::update()
{
	position = position + Point2D<double>(0, velocidadReward);
	// Actualizacion del rect.
	rect.x = position.getX();
	rect.y = position.getY();

	//Salida de limites del reward.
	if (position.getY() <= 0 || position.getY() >= SCRHEIGHT - 10) playST->hasDied(scAnch, objAnch);

	if (playST->mayGrantReward(rect)) {
		rewardCallback();
		playST->hasDied(scAnch, objAnch);
	}

}

void Reward::render() const
{
	tex->render(rect);
}

bool Reward::hit(SDL_Rect _rect, char c)
{
	if ((&_rect) != (&rect) && c != entity && SDL_HasIntersection(&rect, &_rect))
	{
		return true;
	}
	return false;
}