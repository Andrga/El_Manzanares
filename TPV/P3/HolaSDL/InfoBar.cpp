#include "checkML.h"
#include "InfoBar.h"
#include "PlayState.h"


InfoBar::InfoBar(PlayState* gam, Point2D<double> pos, const Texture* tex, int scr) : GameObject(gam), position(pos), canTexture(tex), score(scr)
{
	pos1 = pos; // Para la muestra de vidas cogemos la posicion del infobar.
}

InfoBar::~InfoBar() {}

void InfoBar::update()
{
	cannonLives = game->getCannonLives(); // Cogemos las vidas del cannon.
	if (score != game->returnScore())
	{
		score = game->returnScore();
		cout << "SCORE: " << score << endl;

	}
}

void const InfoBar::render()
{
	//system("color 0A"); // Los colores pintan toda la pantalla -_-
	//system("color 07");


	// Para mostrar las vidas restantes de la nave:
	rect.w = canTexture->getFrameWidth();
	rect.h = canTexture->getFrameHeight();

	for (int i = 0; i < cannonLives; i++)
	{
		rect.x = pos1.getX() + 50 * i; // Para que aparezcan consecutivas.
		rect.y = pos1.getY();
		canTexture->renderFrame(rect, canTexture->getNumRows() - 1, canTexture->getNumColumns() - 2);
	}
}

void const InfoBar::save(ostream& fil) // Guarda: tipo-score.
{
	fil << 7 << " " << score << "\n";
}