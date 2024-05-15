// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

const uint8_t FRUIT_POINTS = 50; // Puntos que da la fruta normal al ser comida.
const uint8_t MIRACLE_POINTS = 100; // Puntos que da la fruta milagrosa al ser comida.
const uint8_t GHOST_POINTS = 200; // Puntos que da el fantasma al ser comido.

class GameCtrlSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::GAMECTRL)

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	inline auto getScore() {
		return score_;
	}

	inline void setScore(unsigned int score) {
		score_ = score;
	}

	inline void incrScore(unsigned int n) {
		score_ += n;
	}

	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;

private:
	unsigned int score_;
};

