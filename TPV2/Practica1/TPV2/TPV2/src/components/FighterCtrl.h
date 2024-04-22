// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class InputHandler;
class Transform;

class FighterCtrl: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)
	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;
private:
	InputHandler &ihdrl;
	Transform *tr_;
	float thrust_;
	float limit_;
};

