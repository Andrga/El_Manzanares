#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	Game game;
	game.run();
	game.~Game();
	return 0;
}
