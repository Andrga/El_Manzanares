#include "SDLApplication.h"
SDLApplication::SDLApplication() {

	setupGame();
}

SDLApplication::~SDLApplication()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLApplication::setupGame()
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

void SDLApplication::run() {
	
}