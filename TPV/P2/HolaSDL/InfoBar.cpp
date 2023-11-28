#include "InfoBar.h"


InfoBar::InfoBar(int scr): score(scr)
{

}

InfoBar::~InfoBar() {}

void InfoBar::update() 
{

}

void const InfoBar::render() 
{
	//system("color 0A");
	cout << "SCORE: " << score << endl;
	//system("color 07");
}

void const InfoBar::save(ofstream& fil) // Guarda: tipo-score.
{
	fil << 3 << " " << score << "\n";
}