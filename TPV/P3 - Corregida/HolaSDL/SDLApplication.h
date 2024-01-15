#pragma once
#include "SDL.h"
#include "texture.h"

#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "EndState.h"
#include "PauseState.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"


#include <vector>
#include <array>

//using namespace std;

const std::string TEXTURE_ROOT = "assets/images/";
const int NUM_TEXTURES = 18;

const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;


const double FRAMERATE = 60;
const double TIMEBETWEENFRAMES = 1000 / FRAMERATE;

// el UFO se llama UFOT para no confundirlo con la clase.
enum TextureName {
	ALIENS, BUNKER, SPACESHIP, STARS, UFOT, BOMB, NUMS, MENUFONDO, NUEVAP,
	CARGARP, SALIR, CONTINUARP, GUARDARP, FONDOP, VOLVERM, GOV, WIN, SHIELD
};


class SDLApplication
{
private:
#pragma region Texturas
	struct textureInfo
	{
		std::string url;
		int rows;
		int cols;
	};

	textureInfo texturesList[NUM_TEXTURES]
	{
			textureInfo{"assets/images/aliens.png", 3, 2},
			textureInfo{"assets/images/bunker.png", 1, 4},
			textureInfo{"assets/images/spaceship.png", 1, 2},
			textureInfo{"assets/images/stars.png",1, 1},
			textureInfo{"assets/images/Ufo.png", 1, 2},
			textureInfo{"assets/objetos/bomb.png", 1, 1},
			textureInfo{"assets/images/numbers.png", 1, 10},
			textureInfo{"assets/fondos/mainMenu.png", 1,1},
			textureInfo{"assets/textos/nuevaPartida.png", 1,1},
			textureInfo{"assets/textos/cargarPartida.png", 1,1},
			textureInfo{"assets/textos/salir.png", 1,1},
			textureInfo{"assets/textos/continuar.png", 1,1},
			textureInfo{"assets/textos/guardarPartida.png", 1,1},
			textureInfo{"assets/fondos/pausaFondo.PNG", 1,1},
			textureInfo{"assets/textos/volverAlMenu.png", 1,1},
			textureInfo{"assets/textos/gameOver.png", 1,1},
			textureInfo{"assets/textos/hasGanado.png", 1,1},
			textureInfo{"assets/objetos/shield_reward.png", 1, 1}


	};
#pragma endregion

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Texture*, NUM_TEXTURES> textures;

	// Maquina de estados
	GameStateMachine* stateMachine = new GameStateMachine();

	// Bucle de juego
	uint32_t frameTime;
	uint32_t startTime;
	bool endGame = false;
	bool _gameOver = false;

	void setupGame();

public:
	SDLApplication();
	~SDLApplication();

	//Metodos base
	void update() { stateMachine->update(); }
	void render() const;
	void run();
	void handleEvents();
	void setEndGame(bool end);

	SDL_Renderer* getRenderer() const { return renderer; }
	//Cambio de estado
	GameStateMachine* getStMachine() const { return stateMachine; }

	//Getters
	Texture* getTexture(TextureName _texNam) const { return textures[_texNam]; }
};

