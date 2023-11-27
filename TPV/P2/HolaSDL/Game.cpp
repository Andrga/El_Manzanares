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
	
	/*cout << "�Cargar partida?\ns=si y n=no" << endl;
	char respuesta;
	bool respuestaCorrecta = false;
	while (!respuestaCorrecta)
	{
		cin >> respuesta;
		if (respuesta=='s')
		{
			cargado();
			respuestaCorrecta = true;
		}
		else if (true)
		{
			respuestaCorrecta = true;
		}
	}*/


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

	if (_gameOver)
	{
		cout << "GAME OVER" << endl;
	}
	cout << "se ha acabao" << endl;
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

	//int i = 0;

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
			nAliens++;
			break;
		case 2:
			newObj = new Bunker(this, 4, Point2D<double>(posx, posy), textures[BUNKER]);
			break;
		default:
			break;
		}
		entities.push_back(newObj); // Metemos la nueva entidad en la lista.

		cout << (entities.begin() == entities.end()); //<< *(entities.end()--);
		it = entities.end();
		it--;
		newObj->setListIterator(it);

		//i++;

		//it = entities.end(); // Ponemos el iterador al final de la lista.

		//newObj->setListIterator(it); // Le pasamos el iterador a la entidad.
	}

	mother->setAlienCount(nAliens);
	//cout << "NAliens: " << nAliens << endl;
	//cout << "NEntidades: " << entities.size() << endl;
}

void Game::update()
{
	auto it = entities.begin();

	// Updatea todos los elementos.
	while (it != entities.end())
	{
		(*it)->update();
		it++;
	}

	// Bucle para eliminar la lista de objetos a eliminar.
	for (auto e : itElims) {
		e = entities.erase(e);
	}
	// Limpia la lista de objetos a eliminar.
	itElims.clear();

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
		if (event.key.keysym.sym == SDLK_ESCAPE) // Salida del juego.
		{
			cout << "Adios hasta nunca." << endl;
			endGame = true;
		}
		else if (event.key.keysym.sym == SDLK_s) // Guardado en archivo.
		{
			save();
		}
		else
		{
			//cout << "Game: funciona porfavor te lo rogamos Vs y c++ del amor hermoso os queremos..." << endl;
			auto it = entities.begin(); // Ponemos el iterador en el principio que es el sitio del cannon.
			dynamic_cast<Cannon*>(*it)->handleEvents(event); // Input.
		}
	}
}

void Game::fireLaser(Point2D<double>& pos, char c)
{
	//cout << "Game: pium pium" << endl;
	SceneObject* newObj = new Laser(this, pos, textures[LASER], c, velocidadLaser);
	entities.push_back(newObj);
	auto it = entities.end();
	it--;
	newObj->setListIterator(it);
}

int Game::getRandomRange(int min, int max)
{
	return  uniform_int_distribution<int>(min, max)(randomGenerator);
}

bool Game::damage(SDL_Rect* _rect, char c)
{
	bool end = false;
	auto it = entities.begin();

	//comprueba el hit de todos los objetos o hasta que encuentra un objeto con el que choca
	while (it != entities.end() && !end)
	{
		end = (*it)->hit(_rect, c);
		it++;
	}
	
	return end;
}

void Game::gameOver() 
{
	_gameOver = true;
	endGame = true;
}

void Game::save() 
{
	ofstream file;
	file.open("assets/maps/guardado.txt");
	
	for (const auto i : entities)
	{
		i->save(file); // Llama a los save de todas las entidades de la lista: 0=Cannon, 1=Alien, 2=ShooterAlien, 4=Bunker, 5=UFO, 6=Laser.	
	}
	mother->save(file); // Llama al save de la MotherShip (3).
	
	file.close(); // Cierra el archivo.
}

void Game::hasDied(list<SceneObject*>::iterator& ite) { itElims.push_back(ite);}

void Game::cargado() 
{

}
