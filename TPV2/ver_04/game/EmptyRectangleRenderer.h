// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>

#include "RenderComponent.h"

class EmptyRectangleRenderer: public RenderComponent {
public:
	EmptyRectangleRenderer();
	EmptyRectangleRenderer(SDL_Color color);
	virtual ~EmptyRectangleRenderer();
	void render(Container *o) override;
private:
	SDL_Color color_;
};

