#include "Game.h"

struct Textura
{
	string name;
	int rows;
	int cols;
};
const Textura texturas[NUM_TEXTURES]
{
		Textura{"aliens",3,2},
		Textura{"bunker",1,4},
		Textura{"spaceship",1,1},
		Textura{"stars",1,1}
};


Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		cout << "No ha punchao la ventana o el renderer :CC";
	else
	{
		for (int i = 0; i < NUM_TEXTURES; i++)
		{
			textures[i] = new Texture(renderer, (TEXTURE_ROOT + texturas[i].name + ".png").c_str(), texturas[i].rows, texturas[i].cols);
		}
	}
	SDL_RenderClear(renderer);
}
Game::~Game() // Destructor
{
	for (const auto e : aliens) {
		delete e;
	}
	for (const auto e : bunkers) {
		delete e;
	}
	for (const auto e : lasers) {
		delete e;
	}
	delete cannon;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::render() {
	if (tiempoTrans == 2500)
	{
		tiempoTrans = 0;
		for (const auto e : aliens)
		{
			e->render();
			e->animation();
		}
	}
	SDL_RenderClear(renderer);
	textures[STARS]->render();
	// Tres filas de aliens.
	for (const auto e : aliens)
	{
		e->render();
	}
	for (const auto e : bunkers)
	{
		e->render();
	}
	for (const auto e : lasers)
	{
		e->render();
	}
	cannon->render(); // Cannon

	SDL_RenderPresent(renderer);
	tiempoTrans++;
}


void Game::update() {
	cout << "update inicio";
	int i = 0;
	while (i < aliens.size())
	{
		if (!aliens[i]->update()) {
			delete aliens[i];
			vector<Alien*>::iterator it = aliens.begin() + i;
			aliens.erase(it);
		}
		else
		{
			i++;
		}
	}
	i = 0;
	while (i < bunkers.size())
	{
		if (!lasers[i]->update()) {
			delete bunkers[i];
			vector<Bunker*>::iterator it = bunkers.begin() + i;
			bunkers.erase(it);
		}
		else
		{
			i++;
		}
	} /*
	i = 0;
	while (i < lasers.size())
	{
		if (!lasers[i]->update()) {
			delete lasers[i];
			vector<Laser*>::iterator it = lasers.begin() + i;
			lasers.erase(it);
		}
		else
		{
			i++;
		}
	}*/
	if (!cannon->update()) {
		delete cannon;
	}
	cout << "update fin";
}

void Game::run() {

	cout << "run inicio";
	int subtipoAlien = 0;
	Game* game = this;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Point2D<double> pos((textures[ALIENS]->getFrameWidth() + 4) * j + 135, (textures[ALIENS]->getFrameHeight() + 3) * i + 30);
			cout << "CARGAN ALIENS";
			//da un error en esta linea que no tengo ni idea de lo que es porque antes funcionaba y ahora no :C (preguntar al profe)
			aliens.push_back(new Alien(pos, subtipoAlien, *textures[ALIENS], *this));

			if (aliens.size() % 11 == 0)
			{
				subtipoAlien++;
			}
		}
	}
	for (int i = 1; i < 5; i++)
	{
		Point2D<double> pos(SCRWIDTH * i / 5 - textures[BUNKER]->getFrameWidth() / 2, SCRHEIGHT - SCRHEIGHT / 4);
		Bunker* newBunker = new Bunker(pos, 4, *textures[BUNKER]);
		bunkers.push_back(newBunker);
	}

	cout << "CARGA BUNKERS";
	Point2D<double> pos(SCRWIDTH / 2 - textures[SPACESHIP]->getFrameWidth() / 2, SCRHEIGHT - SCRHEIGHT / 8);
	cannon = new Cannon(pos, *textures[SPACESHIP], 3, *game);

	cout << "run fin";
	while (!exit)
	{

		cout << "bucle principal inicio";
		handleEvents();
		update();
		render();
		cout << "bucle principal ";
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true; // Input de salida (esc).
		cannon->handleEvent(event); // Input.
	}
}

int Game::getDirection() // Devuelve la direccion de movimiento actual.
{
	return direccionMovimiento;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void Game::cannotMove() // Cambia la direccion de movimeintdo cuando se alcanzan los limites de pantalla.
{
	direccionMovimiento = -direccionMovimiento;
	for (const auto e : aliens)
	{
		e->bajar();
	}
}