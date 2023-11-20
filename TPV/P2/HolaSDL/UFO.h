#pragma once
#include "SceneObject.h"

class UFO: public SceneObject
{
private:
	enum  states { VISIBLE, OCULTO, DESTRUIDO }; // Enumerado de los diferentes estados de la nave.

public:
	UFO();
	void state();
};

