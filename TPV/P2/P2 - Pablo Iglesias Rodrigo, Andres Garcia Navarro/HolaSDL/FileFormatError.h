#pragma once
#include "InvadersError.h"
class FileFormatError : public InvadersError
{
public:
	FileFormatError(const string& mes, string fil) : InvadersError(mes+ fil){}
};

