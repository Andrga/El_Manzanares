#include "InfoBar.h"
#include "Game.h"


InfoBar::InfoBar(Game* gam, Point2D<double> pos, const Texture* tex, int scr) : GameObject(gam), position(pos), canTexture(tex), score(scr)
{

}

InfoBar::~InfoBar() {}

void InfoBar::update() 
{
	CannonLives = game->getCannonLives();
	
}

void const InfoBar::render() 
{
	/*//system("color 0A"); // Los colores pintan toda la pantalla -_-
	cout << "SCORE: " << score << endl;
	//system("color 07");
	rect->y = position.getY();
	for (int i = 0; i < CannonLives; i++)
	{
		rect->x = position.getX() + (10 * i);
		canTexture->renderFrame(*rect, canTexture->getNumRows() - 1, canTexture->getNumColumns() - 2);
	}*/
}

void const InfoBar::save(ofstream& fil) // Guarda: tipo-score.
{
	fil << 3 << " " << score << "\n";
}