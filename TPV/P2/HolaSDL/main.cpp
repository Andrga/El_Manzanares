#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Window* window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
	try
	{

		Game* game = new Game(window);
		game->run();
		delete game;
	}
	catch (const char* e)
	{
		const char* est = "ERROR";
		SDL_ShowSimpleMessageBox(1, est, e, window);
	}
	return 0;
}
