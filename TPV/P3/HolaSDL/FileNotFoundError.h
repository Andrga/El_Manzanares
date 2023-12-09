#pragma once
#include "InvadersError.h"
class FileNotFoundError : public InvadersError
{
public:
	FileNotFoundError(const string& mes) : InvadersError(mes) {}
};

