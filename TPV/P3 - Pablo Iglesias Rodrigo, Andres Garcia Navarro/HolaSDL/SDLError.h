#pragma once
#include "InvadersError.h"
#include "SDL.h"
class SDLError : public InvadersError
{
public:
	SDLError(const string& mes) : InvadersError(mes) {}
};

