#pragma once

#include <SDL.h>

class EventHandler
{
public:
	virtual void handleEvent(const SDL_Event& event) = 0;
};

