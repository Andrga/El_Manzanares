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

#pragma region Texturas

	enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS, UFOT };

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

class SDLApplication
{
private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	array<Texture*, NUM_TEXTURES> textures;

	GameStateMachine stateMachine;

	void setupGame();

public:
	SDLApplication();
	~SDLApplication();

	//Metodos base
	void Update();
	void Render() const;
	void run();

	//Getters
	Texture* getTexture(string _textureName) const;
};

