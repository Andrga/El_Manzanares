// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;

class BallSystem: public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::BALL)

	BallSystem();
	virtual ~BallSystem();

	void resetBall();
	void moveBall();

	void initSystem() override;
	void update() override;
private:
	Transform *ballTr_;
};

