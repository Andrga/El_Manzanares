#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class InmuneComponent : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::IMNUNE_COMPONENT);
	InmuneComponent(bool inmune = false) : inmune_(inmune) {
	};

	virtual ~InmuneComponent() {
	};

	bool getInmune() { return inmune_; }


private:
	bool inmune_;
};

