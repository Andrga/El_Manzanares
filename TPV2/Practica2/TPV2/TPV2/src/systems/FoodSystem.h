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
	void update()override;

	// Para recibir mensajes.
	void recieve(const Message& m) override;

	// Come fruta
	void eatFruit(ecs::entity_t fruit);
private:
	void resetFruits();
	void deleteFruits();
	void setFruits();
	
	int cols_, fils_;
};

