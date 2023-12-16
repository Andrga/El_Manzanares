#include "SDLApplication.h"


#pragma region Configuracion y setting del juego
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
	window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
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
#pragma endregion


//Bucle del juego
void SDLApplication::run() {

	startTime = SDL_GetTicks();
	stateMachine->replaceState(new MainMenuState(this));

	while (!endGame)
	{
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime > TIMEBETWEENFRAMES)
		{
			handleEvents();
			update();
			render();
			startTime = SDL_GetTicks();
		}

	}
}


void SDLApplication::render() const
{
	SDL_RenderClear(renderer);

	stateMachine->render();

	SDL_RenderPresent(renderer);
}

void SDLApplication::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) // Salida del juego.
		{
			cout << "Has cerrado el juego." << endl;
			endGame = true;
		}
		else if (event.key.keysym.sym == (SDLK_s))
		{
			stateMachine->replaceState(new PlayState(renderer, this));
		}
		else // Guardado en archivo.
		{
			stateMachine->handleEvent(event);
		}
	}
}