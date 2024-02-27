// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_scancode.h>

#include "../ecs/Component.h"

class Transform;

class PaddleKBCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::PADDLEKBCTRL)

	PaddleKBCtrl();
	virtual ~PaddleKBCtrl();

	void initComponent() override;
	void update() override;

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

private:
	Transform *tr_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
};

