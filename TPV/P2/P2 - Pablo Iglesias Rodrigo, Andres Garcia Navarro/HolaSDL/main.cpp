#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
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
	catch (FileNotFoundError& e	)
	{
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (SDLError& e)
	{
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (FileFormatError& e)
	{
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (...)
	{
		SDL_ShowSimpleMessageBox(1, "ERROR", "ERROR: Excepcion sin definir.", window);
	}
	return 0;
}
