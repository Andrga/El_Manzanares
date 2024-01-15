#pragma once
#include "InvadersError.h"
class FileNotFoundError : public InvadersError
{
public:
	FileNotFoundError(const std::string& mes) : InvadersError(mes) {}
};

