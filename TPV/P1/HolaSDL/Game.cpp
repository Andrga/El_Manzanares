#include "checkML.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

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

class Error {
protected:
	string mensaje;
public:
	Error(string const& m) : mensaje(m) {};
	const string& what() const {
		return mensaje;
	};
};


Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	try
	{

		window = SDL_CreateWindow("SPACE INAVERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCRWIDTH, SCRHEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr)
		{
			throw Error("Window do not created.");
		}
		else if (renderer == nullptr)
		{
			throw Error("Renderer do not created.");

		}
		else
		{

			for (int i = 0; i < NUM_TEXTURES; i++)
			{
				try
				{
					textures[i] = new Texture(renderer, (TEXTURE_ROOT + texturas[i].name + ".png").c_str(), texturas[i].rows, texturas[i].cols);
					if (textures[i] == nullptr)
					{
						throw Error("Texture do not found.");
					}
				}
				catch (const Error& ex)
				{
					cout << "Error reading texture from archive: " << ex.what() << endl;
				}
			}
		}
		SDL_RenderClear(renderer);
	}
	catch (const Error& ex)
	{
		cout << "Error creating: " << ex.what() << endl;
	}
}

// Destructora
Game::~Game() 
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

//Render de los objetos del juego
void Game::render() {
	//Contador para el cambio de animación
	if (tiempoTrans == 2500)
	{
		tiempoTrans = 0;
		for (const auto e : aliens)
		{
			e->animation();
		}
	}

	//Borra el render anterior
	SDL_RenderClear(renderer);

	//Renderizado de los diferentes elementos del juego
	textures[STARS]->render(); // Fondo
	for (const auto e : aliens) // Aliens
	{
		e->render();
	}
	for (const auto e : bunkers) //Bunkers
	{
		e->render();
	}
	for (const auto e : lasers) // Lasers
	{
		SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
		e->render();
	}
	cannon->render(); // Cannon

	SDL_RenderPresent(renderer);
	tiempoTrans++;
}

//Update de los elementos del juego
void Game::update() {
	int i = 0;
	while (i < aliens.size())
	{
		// Si update del elemento devuelve false, el elemento se elimina
		if (!aliens[i]->update()) {
			delete aliens[i];
			vector<Alien*>::iterator it = aliens.begin() + i;
			aliens.erase(it);
			cout << "alien " << i << " muerto, " << aliens.size() << " restantes" << endl;
		}
		else {
			i++;
		}
	}

	i = 0;
	while (i < bunkers.size())
	{
		// Si update del elemento devuelve false, el elemento se elimina
		if (!bunkers[i]->update()) {
			delete bunkers[i];
			vector<Bunker*>::iterator it = bunkers.begin() + i;
			bunkers.erase(it);
		}
		else
		{
			i++;
		}
	}

	i = 0;
	while (i < lasers.size())
	{
		// Si update del elemento devuelve false, el elemento se elimina
		if (!lasers[i]->update()) {
			delete lasers[i];
			vector<Laser*>::iterator it = lasers.begin() + i;
			lasers.erase(it);
		}
		else
		{
			i++;
		}
	}

	// Si update del elemento devuelve false, el elemento se elimina
	if (!cannon->update()) {
		delete cannon;
		cout << "GAME OVER" << endl;
		exit = true;
	}

	// Si no quedan aliens has ganado
	if (aliens.size() <= 0)
	{
		exit = true;
		cout << "YOU WIN!!" << endl;
	}
}

// Lee el mapa de archivo, crea y situa los objetos y contiene el bucle de juego
void Game::run() {

	try
	{
		//inicialza el ifstream
		std::ifstream map;
		map.open(MAP_PATH);
		if (map.fail())
		{
			throw Error("File not found.");
		}

		// Variables auxiliares
		int objeto, posx, posy, subtAlien;

		// Lectura de objetos
		while (!map.eof())
		{
			map >> objeto >> posx >> posy;
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
				break;
			}
		}
	}
	catch (const Error& ex)
	{
		cout << "Error reading from archive: " << ex.what() << endl;
		exit = true;
	}

	//Bucle principal
	while (!exit)
	{
		handleEvents();
		render();
		update();
	}
}

//Manejo de eventos
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true; // Input de salida (esc).
		cannon->handleEvent(event); // Input.
	}
}

//Devuelve la direccion del movimiento de la nave
int Game::getDirection() // Devuelve la direccion de movimiento actual.
{
	return direccionMovimiento;
}

//Generador de numeros aleatorios en un rango
int Game::getRandomRange(int min, int max) {
	return  uniform_int_distribution<int>(min, max)(randomGenerator);
}

//Es llamado cuando los alienigenas chocan con un borde de pantalla
void Game::cannotMove() // Cambia la direccion de movimeintdo cuando se alcanzan los limites de pantalla.
{
	direccionMovimiento = -direccionMovimiento;
	for (const auto e : aliens)
	{
		e->bajar();
	}
}

//Disparador de laseres
void Game::fireLaser(Point2D<double>position, bool alien)
{
	lasers.push_back(new Laser(position, velocidadLaser, alien, this, renderer)); // Añadimos el laser a la lista de lasers.
}

//Detector de colisiones
void Game::colDetection(Laser* laser) {
	//variables auxiliares
	int i = 0;
	bool collided = false;

	//deteccion de colision laser con laser
	while (i < lasers.size() && !collided)
	{
		if (lasers[i] != laser && SDL_HasIntersection(&laser->getRect(), &lasers[i]->getRect()))
		{
			lasers[i]->hit();
			collided = true;
		}
		i++;
	}
	i = 0;

	//deteccion de colision del laser con los aliens, si el laser proviene del cañon
	while (laser->cannon() && i < aliens.size() && !collided)
	{
		if (SDL_HasIntersection(&laser->getRect(), &aliens[i]->getRect()))
		{
			laser->hit();
			aliens[i]->hit();
			collided = true;
		}
		i++;
	}
	i = 0;

	//deteccion de colision del laser con los bunkeres
	while (i < bunkers.size() && !collided)
	{
		if (SDL_HasIntersection(&laser->getRect(), &bunkers[i]->getRect()))
		{
			laser->hit();
			bunkers[i]->hit();
			collided = true;
		}
		i++;
	}

	//deteccion de colision del laser con el cañon si proviene de los aliens
	if (!laser->cannon() && SDL_HasIntersection(&laser->getRect(), &cannon->getRect()))
	{
		laser->hit();
		cannon->hit();
	}
}
