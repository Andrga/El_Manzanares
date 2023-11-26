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

	auto it = entities.begin();

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

			if (subtAlien == 0) // Shooter Alien.
			{
				newObj = new ShooterAlien(this, Point2D<double>(posx, posy), subtAlien, textures[ALIENS], mother);
			}
			else // Resto de Aliens.
			{
				newObj = new Alien(this, Point2D<double>(posx, posy), subtAlien, textures[ALIENS], mother);
			}
			break;
		case 2:
			newObj = new Bunker(this, 4, Point2D<double>(posx, posy), textures[BUNKER]);
			break;
		default:
			break;
		}
		entities.push_back(newObj); // Metemos la nueva entidad en la lista.

		if (it != entities.end())
			newObj->setListIterator(++it);

		//it = entities.end(); // Ponemos el iterador al final de la lista.

		//newObj->setListIterator(it); // Le pasamos el iterador a la entidad.
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
			cout << "Adios hasta nunca.";
			endGame = true; // Input de salida (esc).
		}
		else
		{
			//cout << "Game: funciona porfavor te lo rogamos Vs y c++ del amor hermoso os queremos..." << endl;
			it = entities.begin(); // Ponemos el iterador en el principio que es el sitio del cannon.
			dynamic_cast<Cannon*>(*it)->handleEvents(event); // Input.
		}
	}
}
void Game::fireLaser(Point2D<double>& pos, char c)
{
	//cout << "Game: pium pium" << endl;
	SceneObject* newObj = new Laser(this, pos, textures[LASER], c, velocidadLaser);
	entities.push_back(newObj);
	it = entities.end();
	newObj->setListIterator(it);

}
int Game::getRandomRange(int min, int max)
{
	return  uniform_int_distribution<int>(min, max)(randomGenerator);
}
void Game::damage(SDL_Rect* _rect, char c)
{
	for (const auto i : entities)
	{
		i->hit(_rect, c);
	}
}
void Game::hasDied(list<SceneObject*>::iterator ite)
{
	cout << "Game: elimina" << endl;
	ite = entities.erase(ite);
	//delete (*ite); // El hueco de la lista se queda vacio.
	cout << "HIJO DE TU MADRE MUERETE :)" << endl;
	entities.erase(ite); // Eliminamos el hueco de la lista.
}