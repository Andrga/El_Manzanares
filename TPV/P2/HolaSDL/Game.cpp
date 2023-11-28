#include "Game.h"

#pragma region constructora/destructora

Game::Game()
{
	cargado();
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

	mother = new Mothership(1);
}

void Game::readMap()
{
	std::ifstream file; 	// Inicialza el ifstream.

	file.open(map);
	if (file.fail())
	{
		//throw Error("File not found.");
	}
	// Variables auxiliares.
	int objeto, subtAlien, lives, state;
	double posx, posy, elapsedTime;
	auto it = entities.begin();

	while (!file.eof()) // Lectura de objetos.
	{
		file >> objeto >> posx >> posy;

		SceneObject* newObj;

		switch (objeto)
		{
		case 0: // Cannon.
			file >> lives >> elapsedTime;
			newObj = new Cannon(this, Point2D<double>(posx, posy), textures[SPACESHIP], lives, elapsedTime);
			break;
		case 1: // Aliens.
			file >> subtAlien;
			newObj = new Alien(this, Point2D<double>(posx, posy), subtAlien, textures[ALIENS], mother);
			nAliens++;
			break;
		case 2: // ShooterAliens.
			file >> subtAlien >> elapsedTime;
			newObj = new ShooterAlien(this, Point2D<double>(posx, posy), subtAlien, textures[ALIENS], mother, elapsedTime);
			nAliens++;
			break;
		case 3:
			mother->setAlienCount(nAliens);
			break;
		case 4: // Bunkers
			file >> lives;
			newObj = new Bunker(this, lives, Point2D<double>(posx, posy), textures[BUNKER]);
			break;
		case 5: //UFO.
			file >> state >> elapsedTime;
			newObj = new UFO();
			break;
		case 6: //Lasers.
			char c;
			file >> c;
			newObj = new Laser(this, Point2D<double>(posx, posy), textures[LASER], c, velocidadLaser);
			break;
		case 7: // Infobar.
			// lo que venga aqui tiene es leido por posx.
			/*5 800 10 0 219
				7 0*/
			break;
		default:
			break;
		}
		entities.push_back(newObj); // Metemos la nueva entidad en la lista.

		//cout << (entities.begin() == entities.end()); //<< *(entities.end()--);
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

#pragma endregion

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

	if (_gameOver)
	{
		cout << "GAME OVER" << endl;
	}
	cout << "se ha acabao" << endl;
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
	if (itElims.size() > 0)
	{
		cout << itElims.size() << endl;

	}
	for (auto e : itElims) {
		entities.erase(e);
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

#pragma region Dano y fin de juego
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

void Game::hasDied(list<SceneObject*>::iterator& ite)
{
	itElims.push_back(ite);
}

#pragma endregion

#pragma region Carga y guardado

void Game::save()
{
	ofstream file;
	file.open("assets/maps/guardado.txt");

	for (const auto i : entities)
	{
		i->save(file); // Llama a los save de todas las entidades de la lista: 0=Cannon, 1=Alien, 2=ShooterAlien, 4=Bunker, 5=UFO, 6=Laser.	
	}
	mother->save(file); // Llama al save de la MotherShip (3). La ponemos la ultima para que se pueda hacer el recuento de Aliens.

	file.close(); // Cierra el archivo.
}
void Game::cargado()
{
	cout << "Cargar mapas?\ng=guardado, o=original,l=lluvia,t=trinchera y u=urgente" << endl;
	char respuesta;
	bool respuestaCorrecta = false;
	while (!respuestaCorrecta)
	{
		cin >> respuesta;
		switch (respuesta)
		{
		case 'g':
			map = map + "guardado.txt";
			respuestaCorrecta = true;
			break;
		case 'o':
			map = map + "original.txt";
			respuestaCorrecta = true;
			break;
		case 't':
			map = map + "trinchera.txt";
			respuestaCorrecta = true;
			break;
		case 'u':
			map = map + "urgente.txt";
			respuestaCorrecta = true;
			break;
		case 'l':
			map = map + "lluvia.txt";
			respuestaCorrecta = true;
			break;

		default:
			break;
		}
	}
}
#pragma endregion