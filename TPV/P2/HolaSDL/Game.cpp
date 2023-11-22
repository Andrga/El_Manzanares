#include "Game.h"

Game::Game() {
	setupGame();
	readMap();
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
		handleEvent();
		update();
		render();
	}
}
void Game::readMap() 
{

	std::ifstream map; 	// Inicialza el ifstream.
	map.open(MAP_PATH);
	if (map.fail())
	{
		//throw Error("File not found.");
	}

	// Variables auxiliares
	int objeto, posx, posy, subtAlien;

	// Lectura de objetos
	while (!map.eof())
	{
		map >> objeto >> posx >> posy;

		switch (objeto)
		{
		case 0:
			entities.push_back(new Cannon(this, Point2D<int>(posx, posy), textures[SPACESHIP], 3, 0));
			it = entities.begin(); // Ponemos el iterador en el primero ahora que tenemos primero.
			//itCannon = it;
		case 1:
			map >> subtAlien;
			entities.push_back(new Alien(this, Point2D<int>(posx, posy), subtAlien, textures[ALIENS], mother));
		case 2:
			entities.push_back(new Bunker(this, 4, Point2D<int>(posx, posy), textures[BUNKER]));
		default:
			break;
		}
		
		
		(*it)->setListOperator(it);
		++it;
	}

}
void Game::update()
{
	
}
void Game::render() 
{
	SDL_RenderClear(renderer);
	textures[STARS]->render(); // Fondo
	for (const auto i : entities)
	{
		i->render();
		//SDL_RenderPresent(renderer);
	}
	SDL_RenderPresent(renderer);
}
void Game::handleEvent() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) endGame = true; // Input de salida (esc).
		//else (*itCannon)->handleEvent(event); // Input.
	}
}