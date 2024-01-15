#include "checkML.h"
#include "InfoBar.h"
#include "PlayState.h"
#include "SDLApplication.h"

using namespace std;

InfoBar::InfoBar(PlayState* plST, SDLApplication* appl, Point2D<double> pos, int scr) : GameObject(plST), playST(plST), position(pos), score(scr)
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.

	// Rects para las vidas del cañon
	// canVid = new SDL_Rect[cannonLives];

	canTexture = playST->getGame()->getTexture(SPACESHIP);
	for (int i = 0; i < cannonLives; i++)
	{
		// Para mostrar las vidas restantes de la nave:
		canVid[i].w = canTexture->getFrameWidth();
		canVid[i].h = canTexture->getFrameHeight();

		//posicionado de las vidas
		canVid[i].x = position.getX() + DIGIT_PITH * i; // Para que aparezcan consecutivas.
		canVid[i].y = position.getY();
	}

	// Rects para la puntuacion
	numTexture = playST->getGame()->getTexture(NUMS);
	for (int i = 0; i < MAX_DIGITS; i++)
	{

		cifrPunt[i].w = numTexture->getFrameWidth();
		cifrPunt[i].h = numTexture->getFrameHeight();

		cifrPunt[i].x = (position.getX() + DIGIT_PITH * (i + 1)) + X_OFFSET; // Para que aparezcan consecutivas.
		cifrPunt[i].y = position.getY() - Y_OFFSET;
	}
}

/*InfoBar::~InfoBar() {
	// Elimina los arrays
	//delete[] canVid;
	//delete[] cifrPunt;

	// Elimina la referencia al playstate
	delete playST;

	// Elimina las referencias a las texturas
	delete canTexture;
	delete numTexture;
}*/

void InfoBar::update()
{
	cannonLives = playST->getCannonLives(); // Cogemos las vidas del cannon.
	if (score != playST->returnScore()) {
		score = playST->returnScore();
	}

}

void InfoBar::render() const
{
	for (int i = 0; i < cannonLives; i++)
	{
		canTexture->renderFrame(canVid[i], 0, 0);
	}

	int scoreAux = score;
	int i = MAX_DIGITS-1;
	while (scoreAux > 0 && i >= 0)
	{
		// dividimos entre 10 porque cogemos el digito derecho para asignarlo a los rect de derecha a izquierda
		numTexture->renderFrame(cifrPunt[i], 0, scoreAux % DIGIT_DIV);
		i--;
		scoreAux = scoreAux / DIGIT_DIV;
	}
}

void InfoBar::save(ostream& fil) const // Guarda: tipo-score.
{
	fil << ID_INFOBAR << " " << score << "\n";
}