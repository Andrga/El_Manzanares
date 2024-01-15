#pragma once
#include <SDL.h>
#include <functional>

#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include "Vector2D.h"
#include "GameState.h"


using SDLEventCallback = std::function<void(void)>;

class Button :public EventHandler, public GameObject
{
private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	SDL_Point point;	// guarda posicion del cursor en click
	SDL_Rect destRect;	// rectangulo del render

	std::list<SDLEventCallback> eventsCB;
	Point2D<double> position;
	Texture* texture;
	int currentFrame;

	// Metodos privados.
	void emit() const;

public:
	Button(GameState* gamSt, Texture* tex, Point2D<double> pos);
	//~Button();

	// Metodos heredados.
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;
	void save(std::ostream& fil) const override{} ;

	// Metodos de clase.
	void connectButton(SDLEventCallback buttonCallback);

};

