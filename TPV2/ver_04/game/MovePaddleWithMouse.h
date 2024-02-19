// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "InputComponent.h"

class MovePaddleWithMouse: public InputComponent {
public:
	MovePaddleWithMouse();
	virtual ~MovePaddleWithMouse();
	void handleInput(Container *o) override;
};

