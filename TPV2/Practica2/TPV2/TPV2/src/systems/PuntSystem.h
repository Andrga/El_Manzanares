#pragma once
#include "../ecs/System.h"

//const uint8_t FRUIT_POINTS = 50; // Puntos que da la fruta normal al ser comida.
//const uint8_t MIRACLE_POINTS = 100; // Puntos que da la fruta milagrosa al ser comida.
//const uint8_t GHOST_POINTS = 200; // Puntos que da el fantasma al ser comido.

class PuntSystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::PUNT)

	//----Constructora.
	PuntSystem();
	//----Destructorora virtual.
	virtual ~PuntSystem();

	//----Init del sistema.
	void initSystem() override;
	//----Update del sistema.
	void update() override;

	//----Para recibir mensajes.
	void recieve(const Message& m) override;


private:
	//----Suma p puntos a los puntos del jugador.
	void addPoints(uint8_t p);
	//----Resetea los puntos del jugador.
	void resetPoints();

	uint8_t points_; // Puntos que tiene el jugador.
};
