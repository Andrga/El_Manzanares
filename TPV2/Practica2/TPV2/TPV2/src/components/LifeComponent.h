#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <iostream>

class Texture;

class LifeComponent : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::LIFE_COMPONENT);
	LifeComponent(int maxLifes = 3, const std::string texture = "heart");

	virtual ~LifeComponent() {

	}
	void hit() {
		lifes_--;
	};

	int getActualLifes() { return lifes_; }
	Texture* getLifeTexture() { return lifeText_; }
	void resetlifes() { lifes_ = maxLifes_; }
	void render() override;

private:
	int lifes_;
	int maxLifes_;

	Texture* lifeText_;
};
