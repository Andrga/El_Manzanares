// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct Points: public ecs::Component {

	__CMPID_DECL__(ecs::cmp::POINTS)

	Points() :
			points_() {
	}
	virtual ~Points() {

	}

	int points_;
};

