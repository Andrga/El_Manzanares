#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Game* game = new Game;
		game->run();
		delete game;
	}
	catch (const std::exception& e)
	{
		SDL_ShowSimpleMessageBox(e);
	}
	return 0;
}
