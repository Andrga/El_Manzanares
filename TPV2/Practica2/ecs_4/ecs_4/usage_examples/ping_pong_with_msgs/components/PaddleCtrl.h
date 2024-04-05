// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_scancode.h>
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
struct PaddleCtrl: ecs::Component {

	__CMPID_DECL__(ecs::cmp::PADDLECTRL)


	enum CtrlType : Uint8 {
		KEYBOARD, MOUSE, AI
	};

	PaddleCtrl() :
			ctrlType_(KEYBOARD), //
			up_(SDL_SCANCODE_UP), //
			down_(SDL_SCANCODE_DOWN), //
			stop_(SDL_SCANCODE_LEFT), //
			speed_(10.0f) //
	{
	}
	virtual ~PaddleCtrl() {
	}

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	inline void setType(CtrlType ctrlType) {
		ctrlType_ = ctrlType;
	}

	CtrlType ctrlType_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
};

