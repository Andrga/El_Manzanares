#pragma once

#include "../ecs/System.h"

const uint32_t TIME_INMUNE = 10000; // Tiempo maximo que puede estar el PacMan en estado inmune (10s).

class ImmunitySystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::INMUNITY);
	// Constructora.
	ImmunitySystem();
	// Destructora.
	virtual ~ImmunitySystem() {};

	// Init del sistema.
	void initSystem() override;
	// Update del sistema.
	void update() override;
	// Para recibir mensajes.
	void recieve(const Message& m) override;
private:

	bool isInmune = false;
	uint32_t time;

};

