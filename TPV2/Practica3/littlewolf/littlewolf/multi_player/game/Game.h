// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once


class LittleWolf;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	LittleWolf *little_wolf_;

};

