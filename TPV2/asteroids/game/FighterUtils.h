// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "FighterFacade.h"

class FighterUtils: public FighterFacade {
public:
	FighterUtils();
	virtual ~FighterUtils();
	void reset_fighter() override;
	void reset_lives() override;
	void create_fighter() override;
	int update_lives(int n) override;
};

