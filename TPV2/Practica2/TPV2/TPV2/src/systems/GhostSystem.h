#pragma once
#include "../ecs/System.h"

class Transform;

class GhostSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::GHOSTS);
	GhostSystem(int ghostLimit = 5);
	virtual ~GhostSystem() {};

	void initSystem() override;
	void update() override;

private:
	void generateGhost();

	int ghostLimit_ = 5;
};