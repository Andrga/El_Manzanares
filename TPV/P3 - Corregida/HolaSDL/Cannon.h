#pragma once
#include "SceneObject.h"
#include "EventHandler.h"

const double TIEMPODISPARO = 25;
constexpr int ID_CANNON = 0;

class Cannon : public EventHandler, public SceneObject
{
private:
	int lives = 3; // Numero de vidas del cannon.
	int direction = 0; // Direcciones: -1 (izquierda), 0 (parado), 1 (derecha).
	double elapsedTime = 0;
	char entity = 'c';

	// Parametros invencibilidad
	bool invincible = false;
	int timer = 0, maxTimer = 200;


public:
	//Constructoras / destructoras
	Cannon(PlayState* gam, Point2D<double> pos, const Texture* tex, int liv, int eTime);
	//~Cannon();

	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c)override;
	void save(std::ostream& fil) const override;
	void handleEvent(const SDL_Event& event) override;

	// Metodos de clase.
	void setInvincible();

	// Getters.
	int getLives() const { return lives; }
	Point2D<double> getPos() const { return position; }
};

