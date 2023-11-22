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
		
		
		
		
		
		
		
		/*map >> objeto >> posx >> posy;
		Point2D<double> pos(posx, posy);

		//clasificacion de objetos
		switch (objeto)
		{
		case 0: // caso de lectura de cannon
			cannon = new Cannon(pos, *textures[SPACESHIP], 3, *this);
			break;
		case 1: // caso de lectura de aliens
			map >> subtAlien;
			aliens.push_back(new Alien(pos, subtAlien, *textures[ALIENS], *this));
			break;
		case 2: // caso de lectura de bunkers
			bunkers.push_back(new Bunker(pos, 4, *textures[BUNKER]));
			break;

		default:
			break;*/
		}
	}





}