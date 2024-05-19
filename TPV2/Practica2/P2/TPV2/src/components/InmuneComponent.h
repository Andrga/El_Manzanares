#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

struct InmuneComponent : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::IMNUNE_COMPONENT);
	InmuneComponent(bool inmune = false) : inmune_(inmune) {
	};

	virtual ~InmuneComponent() {
	};

	void setInmune(bool inmune) {
		inmune_ = inmune;
	};

	bool getImmunity() {
		return inmune_;
	}

	bool inmune_;
};

