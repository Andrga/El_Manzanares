// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"


class StarsSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::STARS)

	StarsSystem();
	virtual ~StarsSystem();
	void initSystem() override;
	void update() override;
	void addStar(unsigned int n);
	void onStarEaten(ecs::entity_t e);
private:
	unsigned int starsLimit_;
	unsigned int currNumOfStars_;
};

