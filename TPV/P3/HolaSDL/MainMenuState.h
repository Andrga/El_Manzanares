#pragma once
#include "GameState.h"
class MainMenuState : public GameState
{
public:
	void update() override;
	void render() const override;

	bool onEnter() override;
	bool onExit() override;
};

