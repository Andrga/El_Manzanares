#include "PlayState.h"


void PlayState::readMap()
{
	std::ifstream file; 	// Inicialza el ifstream.

	file.open(map);
	if (file.fail())
	{
		throw FileNotFoundError("No se puede encuentra el archivo: " + map);
	}
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		throw FileFormatError("El siguiente archivo esta vacio: ", map);
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
			info = new InfoBar(this, Point2D<double>(10, SCRHEIGHT - 30), textures[SPACESHIP], dato1);
		}
		else
		{
			SceneObject* newObj;
			switch (objeto)
			{
			case 0: // Cannon.
				file >> lives >> dato3;
				canion = new Cannon(this, Point2D<double>(dato1, dato2), textures[SPACESHIP], lives, dato3);
				newObj = canion;
				break;
			case 1: // Aliens.
				file >> subtAlien;
				newObj = new Alien(this, Point2D<double>(dato1, dato2), subtAlien, textures[ALIENS], mother);
				nAliens++;
				break;
			case 2: // ShooterAliens.
				file >> subtAlien >> dato3;
				newObj = new ShooterAlien(this, Point2D<double>(dato1, dato2), subtAlien, textures[ALIENS], mother, dato3);
				nAliens++;
				break;
			case 4: // Bunkers.
				file >> lives;
				newObj = new Bunker(this, lives, Point2D<double>(dato1, dato2), textures[BUNKER]);
				break;
			case 5: // UFO.
				file >> state >> dato3;
				newObj = new UFO(this, Point2D<double>(dato1, dato2), textures[UFOT], state, dato3);
				break;
			case 6: // Lasers.
				char c;
				file >> c;
				newObj = new Laser(this, Point2D<double>(dato1, dato2), c, velocidadLaser, renderer);
				break;
				break;
			default:
				break;
			}
			entities.push_back(newObj); // Metemos la nueva entidad en la lista.

			it = entities.end();
			it--;
			newObj->setListIterator(it);

		}
	}
	mother->setAlienCount(nAliens);
}

void PlayState::update()
{
	//Esto va al state machine 
	/*if(!endGame && mother->getAlienCount() > 0)
	{
		handleEvent();
			frameTime = SDL_GetTicks() - startTime;
			if (frameTime > TIMEBETWEENFRAMES)
			{
				update();
					startTime = SDL_GetTicks();
			}
		render();

	}*/

	//Actualizacion de la nave
	mother->update();
	info->update();
	auto it = entities.begin();

	// Updatea todos los elementos.
	while (it != entities.end())
	{
		(*it)->update();
		it++;
	}

	// Bucle para eliminar la lista de objetos a eliminar.
	for (auto e : itElims)
	{
		entities.erase(e);//erase elimina el nodo de la lista
		//deletea ademas de erase
	}

	itElims.clear(); // Limpia la lista de objetos a eliminar.
}