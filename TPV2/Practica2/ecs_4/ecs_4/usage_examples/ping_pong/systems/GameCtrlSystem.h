// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <__mutex_base>
#include <array>

#include "../ecs/System.h"

struct GameState;

class GameCtrlSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::GAMECTRL)

	enum Side {
		LEFT = 0, //
		RIGHT
	};

	enum State {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	void update() override;

	inline State getState() {
		return state_;
	}

	inline unsigned int getScore(std::size_t player) {
		return score_[player];
	}

	void onBallExit(Side side);
	void resetBall();
	void moveBall();

private:

	std::array<unsigned int, 2> score_;
	State state_;
	const unsigned int maxScore_;

};

