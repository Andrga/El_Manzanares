#include "checkML.h"
#include "InfoBar.h"
#include "PlayState.h"
#include "SDLApplication.h"


InfoBar::InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, int scr) : GameObject(plST), playST(plST), position(pos), score(scr)
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.

	canVid = new SDL_Rect[cannonLives];

	canTexture = playST->getGame()->getTexture(SPACESHIP);
	for (int i = 0; i < cannonLives; i++)
	{
		// Para mostrar las vidas restantes de la nave:
		canVid[i].w = canTexture->getFrameWidth();
		canVid[i].h = canTexture->getFrameHeight();

		//posicionado de las vidas
		canVid[i].x = position.getX() + 50 * i; // Para que aparezcan consecutivas.
		canVid[i].y = position.getY();
	}
}

InfoBar::~InfoBar() {}

void InfoBar::update()
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.
	if (score != playST->returnScore())
	{
		score = playST->returnScore();

	}
}

void InfoBar::render() const
{
	for (int i = 0; i < cannonLives; i++)
	{
		canTexture->renderFrame(canVid[i], canTexture->getNumRows() - 1, canTexture->getNumColumns() - 2);
	}
}

void InfoBar::save(ostream& fil) const // Guarda: tipo-score.
{
	fil << 7 << " " << score << "\n";
}