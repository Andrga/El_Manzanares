#include "Game.h"

Game::Game() {
	setupGame();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::setupGame()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
	{
		cout << "Error creacion de ventana" << endl;

	}
	else
	{

		for (int i = 0; i < NUM_TEXTURES; i++)
		{
			textures[i] = new Texture(renderer, (TEXTURE_ROOT + texturesList[i].name + ".png").c_str(), texturesList[i].rows, texturesList[i].cols);
		}
	}
	SDL_RenderClear(renderer);
}

void Game::run() {
	while (!endGame)
	{

	}
}