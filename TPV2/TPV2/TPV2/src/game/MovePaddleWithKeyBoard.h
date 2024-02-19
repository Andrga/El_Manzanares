// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "InputComponent.h"

#include <SDL.h>

class MovePaddleWithKeyBoard: public InputComponent {
public:
	MovePaddleWithKeyBoard();
	virtual ~MovePaddleWithKeyBoard();

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void handleInput(Container *o) override;

private:
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
};


