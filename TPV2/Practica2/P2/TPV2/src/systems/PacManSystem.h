// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMAN)

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;

	// Resetea la posicion del PacMan
	void resetPos();
	// Resetea la vida del PacMan
	void resetLifes();
	// Para recibir mensajes.
	void recieve(const Message& m) override;
private:
	float speed_;
	Transform *pmTR_;
	bool soundPlaying = false;
};
