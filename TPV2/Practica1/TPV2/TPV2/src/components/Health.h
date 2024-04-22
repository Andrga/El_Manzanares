// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"

class Texture;

class Health: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health();
	Health(int lives);
	virtual ~Health();
	void initComponent() override;
	void render() override;
	void set_lives(int l) {
		lives_ = l;
		assert(lives_ >= 0);
	}
	int update_lives(int l) {
		lives_ += l;
		assert(lives_ >= 0);
		return lives_;
	}
private:
	int lives_;
	Texture &img_;
};

