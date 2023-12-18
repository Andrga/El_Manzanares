#include "checkML.h"
#include "InfoBar.h"
#include "PlayState.h"
#include "SDLApplication.h"


InfoBar::InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, int scr) : GameObject(plST), playST(plST), position(pos), score(scr)
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.

	// Rects para las vidas del cañon
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

	// Rects para la puntuacion
	cifrPunt = new SDL_Rect[4];

	numTexture = playST->getGame()->getTexture(NUMS);
	for (int i = 0; i < 4; i++)
	{

		cifrPunt[i].w = numTexture->getFrameWidth();
		cifrPunt[i].h = numTexture->getFrameHeight();

		cifrPunt[i].x = (position.getX() + 50 * (i + 1)) + 400; // Para que aparezcan consecutivas.
		cifrPunt[i].y = position.getY() - 10;
	}
}

InfoBar::~InfoBar() {}

void InfoBar::update()
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.
	if (score != playST->returnScore()) {
		score = playST->returnScore();
		cout << score << endl;
	}

}

void InfoBar::render() const
{
	for (int i = 0; i < cannonLives; i++)
	{
		canTexture->renderFrame(canVid[i], 0, 0);
	}

	int scoreAux = score;
	int i = 3;
	while (scoreAux > 0 && i >= 0)
	{
		numTexture->renderFrame(cifrPunt[i], 0, scoreAux % 10);
		i--;
		scoreAux = scoreAux / 10;
	}
}

void InfoBar::save(ostream& fil) const // Guarda: tipo-score.
{
	fil << 7 << " " << score << "\n";
}