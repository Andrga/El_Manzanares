// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Component.h"

class Container;

class InputComponent: public Component {
public:
	InputComponent() {
	}
	virtual ~InputComponent() {
	}

	virtual void handleInput(Container *o) = 0;
};

