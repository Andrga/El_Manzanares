#pragma once
#include "../ecs/System.h"

class Transform;

class GhostSystem : public ecs::System
{
	GhostSystem();
	virtual ~GhostSystem();

	void initSystem() override;
	void update() override;

};