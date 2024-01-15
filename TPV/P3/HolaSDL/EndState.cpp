#include "EndState.h"
#include "SDLApplication.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "checkML.h"

using namespace std;

EndState::EndState(SDLApplication* _sdlApp, bool win) : GameState(_sdlApp)
{
	rect.y = POS_TITLE_FIN_Y;
	rect.x = POS_TITLE_FIN_X;
	if (win)
	{
		tex = sdlApp->getTexture(WIN);
	}
	else
	{
		tex = sdlApp->getTexture(GOV);

	}
	rect.w = tex->getFrameWidth();
	rect.h = tex->getFrameHeight();

	volverMenu = new Button(this, sdlApp->getTexture(VOLVERM), Point2D<double>(POS_VOLVER_X, POS_VOLVER_Y));
	salir = new Button(this, sdlApp->getTexture(SALIR), Point2D<double>(POS_SALIR_ENX, POS_SALIR_ENY));

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