#pragma once
#include "../ecs/System.h"

class Transform;

class GhostSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::GHOSTS);
	GhostSystem(int ghostLimit = 10);
	virtual ~GhostSystem() {};

	void initSystem() override;
	void update() override;

	void resetGhosts();

	// Para recibir mensajes.
	void recieve(const Message& m) override;

private:
	// Genera fantasmas
	void generateGhost();
	// Mueve fantasma
	void moveGhosts();
	void collGhost(ecs::entity_t ghost);
	// Cambia sprite
	void changeBlueSprite();
	void changeNormalSprite();

	// Cantidad de fantasmas
	int currentGhosts_;
	int ghostLimit_;

	// Cuenta atras generacion de fantasmas
	float maxSpawnTime_;
	float currentTime_;

};