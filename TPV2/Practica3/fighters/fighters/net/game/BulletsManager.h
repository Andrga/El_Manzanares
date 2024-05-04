// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/Vector2D.h"


class BulletManager {
public:
	virtual ~BulletManager() {
	}
	virtual void shoot(Vector2D p, Vector2D v, int width, int height,
			float r) = 0;
};


