#pragma once
#include "InvadersError.h"
#include "SDL.h"
class SDLError : public InvadersError
{
public:
	SDLError(const std::string& mes) : InvadersError(mes) {}
};

