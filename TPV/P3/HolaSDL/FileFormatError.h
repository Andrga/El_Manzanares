#pragma once
#include "InvadersError.h"
class FileFormatError : public InvadersError
{
public:
	FileFormatError(const std::string& mes) : InvadersError(mes){}
};

