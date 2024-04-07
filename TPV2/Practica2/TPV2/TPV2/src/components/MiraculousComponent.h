#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

struct MiraculousComponent : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::MIRACULOUS);

	// Constructora. Pasar los numero en segundos, la constructora lo multiplica por 1000.
	MiraculousComponent(uint32_t n);
	// Destructora.
	virtual ~MiraculousComponent();

	// Init del componente.
	void initComponent() override;
	// Update del componente.
	void update() override;
	// Devuelve si la fruta esta milagrosa o no.
	bool getIsMiracle() { return isMiracle; }

	bool isMiracle = false; // Para controlar si la fruta esta en estado milagrosa o no.
	uint32_t timeToConvert; // Para controlar el tiempo de sdlutils para convertirse.
	uint32_t timeToDesConvert; // Para controlar el tiempo de sdlutils para desconvertirse.
	uint32_t nTime; // Tiempo para que se haga milagrosa.
	uint32_t mTime; // Tiempo para que se deshaga milagrosa.
};

