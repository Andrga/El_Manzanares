#include "checkML.h"
#include "PlayState.h"
#include "SDLApplication.h"
#include "GameState.h"
#include <iostream>
#include <string>

using namespace std;

#pragma region constructora/destructora

PlayState::PlayState(SDLApplication* _sdlApp, bool guardado)
	: renderer(_sdlApp->getRenderer()), GameState(_sdlApp)
{
	if (guardado)
	{
		cargado();
	}
	else
	{

		map = map + "original.txt";
	}
	readMap();

	// Anadir mothership e infobar a la lista de objetos
	addObject(mother);
	addObject(info);
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

	while (!file.eof()) // Lectura de objetos.
	{
		file >> objeto >> dato1 >> dato2;

		if (objeto == 3) // Si es la madre se crea a parte y no se mete en la lista
		{
			file >> dato3;
			mother->setMotherParams(dato1, dato2, dato3);
			//objs.push_back(mother);

		}
		else if (objeto == ID_INFOBAR) // InfoBar no se mete en la lista.
		{
			info = new InfoBar(this, getGame(), Point2D<double>(10, SCRHEIGHT - 30), dato1);
			//objs.push_back(info);
		}
		else
		{
			SceneObject* newObj;
			switch (objeto)
			{
			case ID_CANNON: // Cannon.
				file >> lives >> dato3;
				canion = new Cannon(this, Point2D<double>(dato1, dato2), getGame()->getTexture(SPACESHIP), lives, dato3);
				newObj = canion;
				addEventListener(canion);
				break;
			case ID_ALIEN: // Aliens.
				file >> subtAlien;
				newObj = new Alien(this, Point2D<double>(dato1, dato2), subtAlien, getGame()->getTexture(ALIENS), mother);
				nAliens++;
				break;
			case ID_SHOOTERALIEN: // ShooterAliens.
				file >> subtAlien >> dato3;
				newObj = new ShooterAlien(this, Point2D<double>(dato1, dato2), subtAlien, getGame()->getTexture(ALIENS), mother, dato3);
				nAliens++;
				break;
			case 4: // Bunkers.
				file >> lives;
				newObj = new Bunker(this, lives, Point2D<double>(dato1, dato2), getGame()->getTexture(BUNKER));
				break;
			case ID_UFO: // UFO.
				file >> state >> dato3;
				newObj = new UFO(this, Point2D<double>(dato1, dato2), getGame()->getTexture(UFOT), state, dato3);
				break;
			case ID_LASER: // Lasers.
				char c;
				file >> c;
				newObj = new Laser(this, Point2D<double>(dato1, dato2), c, velocidadLaser);
				break;
			case ID_BOMBA: // Bombas.
				file >> dato3;
				newObj = new Bomb(this, Point2D<double>(dato1, dato2), dato3);
				break;
				/*case 9:
					newObj = new Shield(this, Point2D<double>(dato1, dato2));
					break;*/
			default:
				throw FileFormatError("Objeto inesperado");
				break;
			}

			addSceneObject(newObj);
		}
	}
	mother->setAlienCount(nAliens);
}

void PlayState::addSceneObject(SceneObject* obj) {
	addObject(obj);
	entities.push_back(obj); // Metemos la nueva entidad en la lista

}

#pragma endregion

void PlayState::update()
{
	// Update de la clase base.
	GameState::update();
	if (mother->getAlienCount() <= 0)
	{
		sdlApp->getStMachine()->replaceState(new EndState(sdlApp, true));
	}
}

void PlayState::render() const
{
	getGame()->getTexture(STARS)->render();// Fondo

	//Render de la clase base
	GameState::render();

	// Actualizacion del render
	/*
	for (auto& i : objs)
	{
		i.render();
	}*/

	//info->render();
}

void PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		sdlApp->getStMachine()->pushState(new PauseState(sdlApp, this));
	}
}

#pragma region Dano y fin de juego
void PlayState::fireLaser(const Point2D<double>& pos, char c)
{
	//cout << "Game: pium pium" << endl;
	SceneObject* newObj = new Laser(this, pos, c, velocidadLaser);
	addSceneObject(newObj);
}

void PlayState::fireBomb(const Point2D<double>& position)
{
	//cout << "Lanza bomba" << endl;
	addSceneObject(new Bomb(this, position));
	//entities.push_back(new Bomb(this, position));
}

void PlayState::fireReward(const Point2D<double>& position)
{
	//cout << "Lanza Rewars" << endl;
	addSceneObject(new Reward(this, position, [this]() { canion->setInvincible(); }, sdlApp->getTexture(SHIELD)));
	//entities.push_back(new Reward(this, position, [this]() { canion->setInvincible(); }, sdlApp->getTexture(SHIELD)));
}

bool PlayState::mayGrantReward(SDL_Rect rect)
{
	SDL_Rect canionRect = canion->getRect();
	return SDL_HasIntersection(&rect, &canionRect);
}

bool PlayState::damage(SDL_Rect _rect, char c)
{
	bool end = false;

	//comprueba el hit de todos los objetos o hasta que encuentra un objeto con el que choca
	for (auto& i : entities)
	{
		if (!end) end = i.hit(_rect, c);
		//else i.hit(_rect, c);
	}

	return end;
}
void PlayState::hasDied(GameList<SceneObject, false>::anchor scAnch, GameList<GameObject, true>::anchor objAnch) {
	entities.erase(scAnch);
	eraseObject(objAnch);
}
void PlayState::gameOver()
{
	getGame()->getStMachine()->replaceState(new EndState(sdlApp, false));
}
#pragma endregion

#pragma region Carga y guardado

void PlayState::saveGame()
{
	cout << "introduce numero de archivo:\n";
	string n;
	cin >> n;

	ofstream file("assets/maps/guardado" + n + ".txt");

	save(file);
}
void PlayState::save(std::ostream& file) const
{
	for (auto& i : entities)
	{
		i.save(file); // Llama a los save de todas las entidades de la lista: 0=Cannon, 1=Alien, 2=ShooterAlien, 4=Bunker, 5=UFO, 6=Laser, 8=Bomba, 9=Shield.
	}
	mother->save(file); // Llama al save de la MotherShip (3). La ponemos la ultima para que se pueda hacer el recuento de Aliens.
	info->save(file); // Llama al save del infobar (7)
}

void PlayState::cargado()
{
	cout << "introduce numero de archivo:\n";
	string n;
	cin >> n;

	map = map + "guardado" + n + ".txt";
}
#pragma endregion


bool PlayState::onEnter() {
	cout << "Entrando PlayState\n";
	return true;
}
bool PlayState::onExit() {
	cout << "Saliendo PlauState\n";
	return true;
}

int PlayState::getRandomRange(int min, int max) {
	return  uniform_int_distribution<int>(min, max)(randomGenerator);
}