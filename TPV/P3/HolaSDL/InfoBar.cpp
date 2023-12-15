#include "checkML.h"
#include "InfoBar.h"
#include "PlayState.h"


InfoBar::InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, const Texture* canTex, int scr) : GameObject(appl), playST(plST), position(pos), canTexture(canTex), score(scr)
{
	pos1 = pos; // Para la muestra de vidas cogemos la posicion del infobar.
}

InfoBar::~InfoBar() {}

void InfoBar::update()
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.
	if (score != playST->returnScore())
	{
		score = playST->returnScore();
		cout << "SCORE: " << score << endl;

	}
	// Para mostrar las vidas restantes de la nave:
	rect.w = canTexture->getFrameWidth();
	rect.h = canTexture->getFrameHeight();

	for (int i = 0; i < cannonLives; i++)
	{
		rect.x = pos1.getX() + 50 * i; // Para que aparezcan consecutivas.
		rect.y = pos1.getY();
	}
}

void InfoBar::render() const
{
	for (int i = 0; i < cannonLives; i++)
	{
		canTexture->renderFrame(rect, canTexture->getNumRows() - 1, canTexture->getNumColumns() - 2);
	}
}

void InfoBar::save(ostream& fil) const // Guarda: tipo-score.
{
	fil << 7 << " " << score << "\n";
}