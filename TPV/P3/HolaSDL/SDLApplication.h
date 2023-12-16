#pragma once
#include "SDL.h"
#include "texture.h"

#include "GameStateMachine.h"

#include "InvadersError.h"
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"


#include <vector>
#include <array>

using namespace std;

const string TEXTURE_ROOT = "assets/images/";
const int NUM_TEXTURES = 5;

const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;


const double FRAMERATE = 20;
const double TIMEBETWEENFRAMES = 1000 / FRAMERATE;

// el UFO se llama UFOT para no confundirlo con la clase.
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS, UFOT };


class SDLApplication
{
private:
#pragma region Texturas
	struct textureInfo
	{
		string name;
		int rows;
		int cols;
	};

	textureInfo texturesList[NUM_TEXTURES]
	{
			textureInfo{"aliens", 3, 2},
			textureInfo{"bunker", 1, 4},
			textureInfo{"spaceship", 1, 2},
			textureInfo{"stars",1, 1},
			textureInfo{"Ufo", 1, 2}
	};
#pragma endregion

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	array<Texture*, NUM_TEXTURES> textures;

	// Maquina de estados
	GameStateMachine stateMachine;

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
	void update() { stateMachine.update(); }
	void render() const {stateMachine.render(); }
	void run();

	//Getters
	Texture* getTexture(TextureName _texNam) const { return textures[_texNam]; }
};

