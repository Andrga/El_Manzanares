#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <iostream>


struct GhostMotion : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::GHOST_MOTION);
	GhostMotion() {};

	virtual ~GhostMotion() {

	}

	inline bool shouldUpdate(Uint32 currTime) {
		if (lastUpdate_ + updateFreq_ < currTime) {
			lastUpdate_ = currTime;
			return true;
		}
		else {
			return false;
		}
	}

	Uint32 updateFreq_;
	Uint32 lastUpdate_;
	float rot_;
	float sizeLimit_;
};

