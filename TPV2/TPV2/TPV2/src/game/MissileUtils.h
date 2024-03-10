#pragma once

#include "MissileFacade.h"

#include "../sdlutils/SDLUtils.h"

class Vector2D;
class RandomNumberGenerator;

class MissileUtils : public MissileFacade
{
public:
	MissileUtils();
	virtual ~MissileUtils();
	void create_missiles() override;
	void remove_all_missiles() override;

private:
	RandomNumberGenerator& rand_;
	ecs::Manager* mngr_;

	int screenWidth = sdlutils().width(), 
		screenHeight = sdlutils().height();
};