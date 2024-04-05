// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"

struct StarMotion: public ecs::Component {

	__CMPID_DECL__(ecs::cmp::STARMOTION)

	StarMotion() :
			updateFreq_(), lastUpdate_(), rot_(), sizeLimit_() {
	}

	virtual ~StarMotion() {
	}

	inline bool shouldUpdate(Uint32 currTime) {
		if (lastUpdate_ + updateFreq_ < currTime) {
			lastUpdate_ = currTime;
			return true;
		} else {
			return false;
		}
	}

	Uint32 updateFreq_;
	Uint32 lastUpdate_;
	float rot_;
	float sizeLimit_;
};

