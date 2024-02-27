// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

class Transform: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::TRANSFORM)

	Transform() :
			pos_(), vel_(), width_(), height_(), rot_() {
	}

	Transform(Vector2D pos, Vector2D vel, float w, float h, float r) :
			pos_(pos), vel_(vel), width_(w), height_(h), rot_(r) {
	}

	virtual ~Transform() {
	}

	void init(Vector2D pos, Vector2D vel, float w, float h, float r) {
		pos_ = pos;
		vel_ = vel;
		width_ = w;
		height_ = h;
		rot_ = r;
	}

	Vector2D& getPos() {
		return pos_;
	}
	Vector2D& getVel() {
		return vel_;
	}

	float getWidth() {
		return width_;
	}

	void setWidth(float w) {
		width_ = w;
	}

	float getHeight() {
		return height_;
	}

	void setHeight(float h) {
		height_ = h;
	}

	float getRot() {
		return rot_;
	}

	void setRot(float r) {
		rot_ = r;
	}

	void update() override {
		pos_ = pos_ + vel_;
	}

private:
	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rot_;
};

