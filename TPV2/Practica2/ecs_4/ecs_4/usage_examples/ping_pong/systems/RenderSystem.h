// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDER)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;

private:
	void drawMsgs();
	void drawScore();
	void drawBall();
	void drawPaddles();


};

