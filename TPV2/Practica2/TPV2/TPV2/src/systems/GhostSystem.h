#pragma once
#include "../ecs/System.h"

class Transform;

class GhostSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::GHOSTS);
	GhostSystem(int ghostLimit = 2);
	virtual ~GhostSystem() {};

	void initSystem() override;
	void update() override;

private:
	void generateGhost();

	int currentGhosts_;
	int ghostLimit_;
};