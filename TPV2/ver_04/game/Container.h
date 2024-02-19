// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "GameObject.h"

class InputComponent;
class RenderComponent;
class PhysicsComponent;

class Container: public GameObject {
public:
	Container();
	virtual ~Container();

	void handleInput() override;
	void update() override;
	void render() override;

	inline void addComponent(InputComponent *ic) {
		ic_.push_back(ic);
	}

	inline void addComponent(RenderComponent *rc) {
		rc_.push_back(rc);
	}

	inline void addComponent(PhysicsComponent *pc) {
		pc_.push_back(pc);
	}

private:
	std::vector<InputComponent*> ic_;
	std::vector<RenderComponent*> rc_;
	std::vector<PhysicsComponent*> pc_;
};

