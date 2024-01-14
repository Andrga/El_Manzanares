#include "EndState.h"
#include "SDLApplication.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "checkML.h"

using namespace std;

EndState::EndState(SDLApplication* _sdlApp, bool win) : GameState(_sdlApp)
{
	rect.y = 100;
	if (win)
	{
		rect.x = 300;
		tex = sdlApp->getTexture(WIN);
	}
	else
	{
		rect.x = 300;
		tex = sdlApp->getTexture(GOV);

	}
	rect.w = tex->getFrameWidth();
	rect.h = tex->getFrameHeight();

	volverMenu = new Button(this, sdlApp->getTexture(VOLVERM), Point2D<double>(250, 250));
	salir = new Button(this, sdlApp->getTexture(SALIR), Point2D<double>(350, 400));

	addObject(volverMenu);
	addObject(salir);

	addEventListener(volverMenu);
	addEventListener(salir);

	volverMenu->connectButton([this]() { sdlApp->getStMachine()->replaceState(new MainMenuState(sdlApp)); });
	salir->connectButton([this]() { sdlApp->setEndGame(true); });
}
void EndState::update()
{
	for (GameObject& a : objs) {
		a.update();
	}
}
void EndState::render() const
{
	sdlApp->getTexture(STARS)->render();
	tex->render(rect);

	for (GameObject& a : objs) {
		a.render();
	}
}

bool EndState::onEnter()
{
	cout << "Entrando EndState\n";
	return true;
}

bool EndState::onExit()
{
	cout << "Saliendo EndState\n";
	return true;
}