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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	if (window == nullptr || renderer == nullptr)
	{
		throw SDLError("Error en SDL: "s + SDL_GetError());
		//cout << "Error creacion de ventana" << endl;
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
	startTime = SDL_GetTicks();


	while (!endGame && mother->getAlienCount() > 0)
	{
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime > TIMEBETWEENFRAMES)
		{
			handleEvent();
			update();
			startTime = SDL_GetTicks();
		}
		render();

	}

	if (_gameOver)
	{
		//system("color 04");
		cout << "GAME OVER" << endl;
		//system("color 07");
	}
	else if (mother->getAlienCount() <= 0)
	{
		cout << "WIN" << endl;
	}
}