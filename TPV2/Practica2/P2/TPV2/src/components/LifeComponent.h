#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <iostream>

class Texture;

struct LifeComponent : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::LIFE_COMPONENT);
	LifeComponent(int maxLifes = 3, const std::string texture = "heart");

	virtual ~LifeComponent() {

	}

	//	Choque con un fantasma
	void hit();

	int getActualLifes() { return lifes_; }
	Texture* getLifeTexture() { return lifeText_; }
	void resetLifes() { lifes_ = maxLifes_; }
	void render() override;

	int lifes_;
	int maxLifes_;

	Texture* lifeText_;
};

