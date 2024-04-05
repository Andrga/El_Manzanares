// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;
struct PaddleCtrl;
class Vector2D;

class PaddlesSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PADDLES)

	PaddlesSystem();
	virtual ~PaddlesSystem();
	void update() override;
	void initSystem() override;

private:
	void movePaddle(ecs::entity_t);
	void moveWithKeyboard(PaddleCtrl*, Transform*);
	void moveWithMouse(PaddleCtrl*, Transform*);
	void moveWithAI(PaddleCtrl*, Transform*);
	bool ballComingTowardsPaddle(const Vector2D&);

	Transform *ballTr_;

};

