// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

class GameCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GAMECTRL)

	GameCtrl();
	virtual ~GameCtrl();

	inline void onStarDeath() {
		currNumOfStars_--;
	}

	inline void onStarEaten() {
		currNumOfStars_--;
		score_++;
	}

	void initComponent() override;
	void update() override;
	void render() override;

private:
	void createStart(unsigned int n);

	unsigned int currNumOfStars_;
	unsigned int score_;
	unsigned int starsLimit_;
};

