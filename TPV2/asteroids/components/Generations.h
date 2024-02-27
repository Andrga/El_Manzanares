// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Generations: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::GENERATIONS)

	Generations(int gen) :
			gen_(gen) {
	}

	virtual ~Generations() {
	}

	int getGenerations() {
		return gen_;
	}

	void setGeneration(int n) {
		gen_ = n;
	}
private:
	int gen_;
};

