// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class GameState;

class GameInfoMsgs: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GAMEINFOMSGS)

	GameInfoMsgs();
	virtual ~GameInfoMsgs();
	void initComponent() override;
	void render() override;
private:
	GameState *gameState_;
};

