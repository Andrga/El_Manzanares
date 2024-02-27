// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class FighterFacade {
public:
	FighterFacade() {
	}
	virtual ~FighterFacade() {
	}
	void virtual create_fighter() = 0;
	void virtual reset_fighter() = 0;
	void virtual reset_lives() = 0;
	int virtual update_lives(int n) = 0;
};

