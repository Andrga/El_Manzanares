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

using namespace std;

const string TEXTURE_ROOT = "assets/images/";
const int NUM_TEXTURES = 5;

const double SCRWIDTH = 800;
const double SCRHEIGHT = 600;


const double FRAMERATE = 60;
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
	void render() const;
	void run();
	void handleEvents();

	//Cambio de estado
	void playStateChange(bool sustituye)
	{
		sustituye ? stateMachine.replaceState(new PlayState(renderer, this)) :
			stateMachine.pushState(new PlayState(renderer, this));
	}
	void mainMenuStateChange(bool sustituye)
	{
		sustituye ? stateMachine.replaceState(new MainMenuState(this)) :
			stateMachine.pushState(new MainMenuState(this));
	}
	void pauseStateChange(bool sustituye)
	{
		sustituye ? stateMachine.replaceState(new PauseState(this)) :
			stateMachine.pushState(new PauseState(this));
	}
	void endStateChange(bool sustituye)
	{
		sustituye ? stateMachine.replaceState(new EndState(this)) :
			stateMachine.pushState(new EndState(this));
	}
	void popState();

	//Getters
	Texture* getTexture(TextureName _texNam) const { return textures[_texNam]; }
};
