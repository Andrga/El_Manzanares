#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

void firstTest()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
