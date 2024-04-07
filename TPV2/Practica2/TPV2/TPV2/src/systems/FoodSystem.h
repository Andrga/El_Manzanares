#pragma once
#include "../ecs/System.h"

class FoodSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FRUITS);
	FoodSystem();
	virtual ~FoodSystem() {

	};

	void initSystem()override;

	// Para recibir mensajes.
	void recieve(const Message& m) override;

	void eatFruit(ecs::entity_t fruit);
private:

	void setFruits();
	
	int cols_, fils_;
};

