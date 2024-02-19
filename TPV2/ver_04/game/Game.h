// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "GameManager.h"

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Container;
class GameManager;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	void checkCollisions();

	GameManager *gm_;
	Container *leftPaddle_;
	Container *rightPaddle_;
	Container *ball_;
	std::vector<GameObject*> objs_;
};

