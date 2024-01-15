#pragma once
#include "SceneObject.h"
#include "checkML.h"
#include "Cannon.h"
#include <functional> 
#include "texture.h"


using SDLEventCallback = std::function<void(void)>;

class Reward:public SceneObject
{
private:
	char entity = 'r';
	SDL_Renderer* renderer = nullptr;
	Texture* tex;
	SDLEventCallback rewardCallback;

public:

	//Constructoras / destructoras
	Reward(PlayState* playST, Point2D<double> pos, SDLEventCallback rew, Texture* _tex);
	//~Reward();

	// Metodos heredados.
	void update() override;
	void render() const override;
	bool hit(SDL_Rect rect, char c) override;
};

