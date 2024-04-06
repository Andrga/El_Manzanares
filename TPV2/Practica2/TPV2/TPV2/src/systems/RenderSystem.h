// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Texture;
struct Transform;
struct ImageWithFrames;

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDER)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawGhosts();
	void drawPacMan();
	void drawLifes();
	void drawFruits();
	void drawImageWithFrames(ImageWithFrames*);
	//void drawMsgs();
	void draw(Transform *tr, Texture *tex);
};

