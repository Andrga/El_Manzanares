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
	startTime = SDL_GetTicks();
	while (!endGame)
	{
		handleEvent();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime > TIMEBETWEENFRAMES)
		{
			update();
			startTime = SDL_GetTicks();
		}
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

	int objeto, posx, posy, subtAlien; // Variables auxiliares.

	while (!map.eof()) // Lectura de objetos.
	{
		map >> objeto >> posx >> posy;

		SceneObject* newObj;

		switch (objeto)
		{
		case 0:

			newObj = new Cannon(this, Point2D<double>(posx, posy), textures[SPACESHIP], 3, 0);
			//cannonPtr = dynamic_cast<Cannon*>(newObj);
			break;
		case 1:
			map >> subtAlien;
			newObj = new Alien(this, Point2D<double>(posx, posy), subtAlien, textures[ALIENS], mother);
			break;
		case 2:
			newObj = new Bunker(this, 4, Point2D<double>(posx, posy), textures[BUNKER]);
			break;
		default:
			break;
		}
		entities.push_back(newObj); // Metemos la nueva entidad en la lista.

		it = entities.end(); // Ponemos el iterador al final de la lista.

		newObj->setListOperator(it); // Le pasamos el iterador a la entidad.
	}
}
void Game::update()
{
	for (const auto i : entities)
	{
		if (!i->update())
		{
			
		}
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);

	textures[STARS]->render(); // Fondo

	for (const auto i : entities)
	{
		i->render();
	}
	SDL_RenderPresent(renderer); // Presentacion del render.
}
void Game::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !endGame)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			cout << "Adiós hasta nunca.";
			endGame = true; // Input de salida (esc).
		}
		else
		{
			cout << "Game: funciona porfavor te lo rogamos Vs y c++ del amor hermoso os queremos..." << endl;
			it = entities.begin(); // Ponemos el iterador en el principio que es el sitio del cannon.
			dynamic_cast<Cannon*>(*it)->handleEvents(event); // Input.
		}
	}
}
void Game::fireLaser(Point2D<double> &pos, char c) 
{
	//entities.push_back(new Laser(this, ));

}