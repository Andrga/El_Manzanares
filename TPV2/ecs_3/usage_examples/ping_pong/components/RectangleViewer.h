// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_pixels.h>

#include "../ecs/Component.h"

class Transform;

class RectangleViewer: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::RECTANGLEVIEWER)

	RectangleViewer();
	RectangleViewer(SDL_Color color, bool empty = false);
	virtual ~RectangleViewer();

	inline void init(SDL_Color color, bool empty = false) {
		color_ = color;
		empty_ = empty;
	}

	void initComponent() override;
	void render() override;
private:
	Transform *tr_;
	bool empty_;
	SDL_Color color_;

};

