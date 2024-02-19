// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "InputComponent.h"

class GameCtrl: public InputComponent {
public:
	GameCtrl();
	virtual ~GameCtrl();
	void handleInput(Container *o) override;
};

