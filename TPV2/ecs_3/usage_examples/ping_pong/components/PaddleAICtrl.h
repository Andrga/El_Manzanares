// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;
class Vector2D;

class PaddleAICtrl: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::PADDLAICTRL)

	PaddleAICtrl();
	virtual ~PaddleAICtrl();
	void initComponent() override;
	void update() override;

private:
	bool ballComingTowardsPaddle(const Vector2D &pos);

	Transform *tr_;
	Transform *ballTr_;
};

