// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_pixels.h>
#include "RenderComponent.h"

class RectangleRenderer: public RenderComponent {
public:
	RectangleRenderer();
	RectangleRenderer(SDL_Color color);
	virtual ~RectangleRenderer();

	virtual void render(Container *o) override;

private:
	SDL_Color color_;
};

