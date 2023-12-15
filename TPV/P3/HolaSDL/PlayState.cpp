#include "checkML.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include <iostream>
#include <string>

#pragma region constructora/destructora

PlayState::PlayState(SDL_Renderer* rend)
	: renderer(rend)
{

	cargado();
	readMap();

}

PlayState::~PlayState()
{
}

void PlayState::readMap()
{
	std::ifstream file; 	// Inicialza el ifstream.

	file.open(map);
	if (file.fail())
	{
		throw FileNotFoundError("No se puede encuentra el archivo: "s + map);
	}
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		throw FileFormatError("El siguiente archivo esta vacio: "s + map);
	}

	// Variables auxiliares.
	int objeto, subtAlien, lives, state, nAliens = 0;
	double dato1, dato2, dato3;
	auto it = entities.begin();

	while (!file.eof()) // Lectura de objetos.
	{
		file >> objeto >> dato1 >> dato2;

		if (objeto == 3) // Si es la madre se crea a parte y no se mete en la lista
		{
			file >> dato3;
			mother->setMotherParams(dato1, dato2, dato3);
		}
		else if (objeto == 7) // InfoBar no se mete en la lista.
		{
			info = new InfoBar(this, getGame(), Point2D<double>(10, SCRHEIGHT - 30), getGame()->getTexture("spaceship"), dato1);
		}
		else
		{
			SceneObject* newObj;
			switch (objeto)
			{
			case 0: // Cannon.
				file >> lives >> dato3;
				canion = new Cannon(this, Point2D<double>(dato1, dato2), getGame()->getTexture("spaceship"), lives, dato3);
				newObj = canion;
				break;
			case 1: // Aliens.
				file >> subtAlien;
				newObj = new Alien(this, Point2D<double>(dato1, dato2), subtAlien, getGame()->getTexture("aliens"), mother);
				nAliens++;
				break;
			case 2: // ShooterAliens.
				file >> subtAlien >> dato3;
				newObj = new ShooterAlien(this, Point2D<double>(dato1, dato2), subtAlien, getGame()->getTexture("aliens"), mother, dato3);
				nAliens++;
				break;
			case 4: // Bunkers.
				file >> lives;
				newObj = new Bunker(this, lives, Point2D<double>(dato1, dato2), getGame()->getTexture("bunker"));
				break;
			case 5: // UFO.
				file >> state >> dato3;
				newObj = new UFO(this, Point2D<double>(dato1, dato2), getGame()->getTexture("Ufo"), state, dato3);
				break;
			case 6: // Lasers.
				char c;
				file >> c;
				newObj = new Laser(this, Point2D<double>(dato1, dato2), c, velocidadLaser, renderer);
				break;
				break;
			default:
				throw FileFormatError("Objeto inesperado");
				break;
			}
			entities.push_back(newObj); // Metemos la nueva entidad en la lista
		}
	}
	mother->setAlienCount(nAliens);
}

#pragma endregion

void PlayState::run() {
	startTime = SDL_GetTicks();


	while (!endGame && mother->getAlienCount() > 0)
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
		//system("color 04");
		cout << "GAME OVER" << endl;
		//system("color 07");
	}
	else if (mother->getAlienCount() <= 0)
	{
		cout << "WIN" << endl;
	}
}

void PlayState::update()
{
	//Actualizacion de la nave
	mother->update();
	info->update();

	// Updatea todos los elementos.
	for (auto i : entities)
	{
		i.update();
	}


	// --- Utilizamos el metodo erase de la clase gamelist ---
	// 
	//// Bucle para eliminar la lista de objetos a eliminar.
	//for (auto e : itElims)
	//{
	//	entities.erase(e);//erase elimina el nodo de la lista
	//	//deletea ademas de erase
	//	iu++;
	//}

	//itElims.clear(); // Limpia la lista de objetos a eliminar.
}

const void PlayState::render()
{
	SDL_RenderClear(renderer);

	getGame()->getTexture("stars")->render();// Fondo

	// Actualizacion del render
	for (auto i : entities)
	{
		i.render();
	}

	info->render();
	SDL_RenderPresent(renderer); // Presentacion del render.
}

void PlayState::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !endGame)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE) // Salida del juego.
		{
			cout << "Has cerrado el juego." << endl;
			endGame = true;
		}
		else if (event.key.keysym.sym == SDLK_s) // Guardado en archivo.
		{
			string num;
			cout << "Numero de guardado de partida:";
			cin >> num;

			ofstream file;
			file.open("assets/maps/guardado" + num + ".txt");
			save(file);

			file.close();
		}
		//else if (event.key.keysym.sym == SDLK_l) // Cargar partida.
		//{
		//	save();
		//}

		else
		{
			//cout << "Game: funciona porfavor te lo rogamos Vs y c++ del amor hermoso os queremos..." << endl;
			canion->handleEvents(event); // Input.
		}
	}
}

#pragma region Dano y fin de juego
void PlayState::fireLaser(Point2D<double>& pos, char c)
{
	//cout << "Game: pium pium" << endl;
	SceneObject* newObj = new Laser(this, pos, c, velocidadLaser, renderer);
	entities.push_back(newObj);
}

//int PlayState::getRandomRange(int min, int max)
//{
//	return  uniform_int_distribution<int>(min, max)(randomGenerator);
//}

bool PlayState::damage(SDL_Rect _rect, char c)
{
	bool end = false;

	//comprueba el hit de todos los objetos o hasta que encuentra un objeto con el que choca
	for (auto e : entities) 
	{
		if (!end) end = e.hit(_rect, c);
	}

	return end;
}

void PlayState::gameOver()
{
	_gameOver = true;
	endGame = true;
}

void PlayState::hasDied(GameList<SceneObject, false>::anchor anch)
{
	entities.erase(anch);
}

#pragma endregion

#pragma region Carga y guardado
//void PlayState::save(string num)
//{
//	ofstream file;
//	file.open("assets/maps/guardado.txt");
//
//	for (const auto i : entities)
//	{
//		i->save(file); // Llama a los save de todas las entidades de la lista: 0=Cannon, 1=Alien, 2=ShooterAlien, 4=Bunker, 5=UFO, 6=Laser.	
//	}
//	mother->save(file); // Llama al save de la MotherShip (3). La ponemos la ultima para que se pueda hacer el recuento de Aliens.
//	info->save(file);
//
//	file.close(); // Cierra el archivo.
//}

const void PlayState::save(ostream& file)
{
	for (auto i : entities)
	{
		i.save(file); // Llama a los save de todas las entidades de la lista: 0=Cannon, 1=Alien, 2=ShooterAlien, 4=Bunker, 5=UFO, 6=Laser.	
	}
	mother->save(file); // Llama al save de la MotherShip (3). La ponemos la ultima para que se pueda hacer el recuento de Aliens.
	info->save(file);
}

void PlayState::cargado()
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

			cout << "Respuesta no valida." << endl;
			break;
		}
	}
}
#pragma endregion

//void PlayState::invencible() // Para poner la nave invencible, llamado por el UFO.
//{
//	canion->setInvincible();
//}

//int PlayState::getCannonLives() // Devuelve el numero de vidas del cannon.
//{
//	return canion->getLives();
//}
//
//void PlayState::addScore(int points)
//{
//	score += points;
//}