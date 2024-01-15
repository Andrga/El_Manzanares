#include "Button.h"
#include "checkML.h"

Button::Button(GameState* gamSt, Texture* tex, Point2D<double> pos)
	: GameObject(gamSt), texture(tex), position(pos)
{
	currentFrame = MOUSE_OUT;

	destRect = SDL_Rect{ (int)pos.getX(), (int)pos.getY(), texture->getFrameWidth(), texture->getFrameHeight()};
}

void Button::update()
{
	SDL_GetMouseState(&point.x, &point.y);

	// Point esta dentro del rango destRect?
	if (SDL_PointInRect(&point, &destRect)) {
		currentFrame = MOUSE_OVER;
		//cout << "MOUSE OVERRRRRRRRRRRRRRRRRRRRRRRRRRRR\n";
	}
	else currentFrame = MOUSE_OUT;
}


void Button::render() const
{
	texture->render(destRect);
}


void Button::handleEvent(const SDL_Event& event) 
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && currentFrame == MOUSE_OVER) {

		SDL_Point point{ event.button.x, event.button.y };

		if (SDL_PointInRect(&point, &destRect)) {
			currentFrame = CLICKED;
			emit();
		}
	}
}

void Button::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback buttonCallback : eventsCB)
	{
		buttonCallback();
	}
}

void Button::connectButton(SDLEventCallback buttonCallback)
{
	eventsCB.push_back(buttonCallback);
}