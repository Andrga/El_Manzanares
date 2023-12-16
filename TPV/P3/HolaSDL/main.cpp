#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "SDLApplication.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
using namespace std;

int main(int argc, char* argv[])
{

	try
	{
		SDLApplication* sdlApp = new SDLApplication();
		sdlApp->run();
		delete sdlApp;
	}
	catch (FileNotFoundError& e)
	{
		SDL_Window* window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1, 1, SDL_WINDOW_SHOWN);
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (SDLError& e)
	{
		SDL_Window* window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1, 1, SDL_WINDOW_SHOWN);
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (FileFormatError& e)
	{
		SDL_Window* window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1, 1, SDL_WINDOW_SHOWN);
		SDL_ShowSimpleMessageBox(1, "ERROR", e.what(), window);
	}
	catch (...)
	{
		SDL_Window* window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1, 1, SDL_WINDOW_SHOWN);
		SDL_ShowSimpleMessageBox(1, "ERROR", "ERROR: Excepcion sin definir.", window);
	}
	return 0;
}
