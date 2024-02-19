// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "InputComponent.h"

class GameObject;
class Vector2D;

class AIPaddle: public InputComponent {
public:
	AIPaddle(GameObject *ball);
	virtual ~AIPaddle();
	void handleInput(Container *o) override;

private:
	bool ballComingTowardsPaddle(const Vector2D &pos);

	GameObject *ball_;
};

