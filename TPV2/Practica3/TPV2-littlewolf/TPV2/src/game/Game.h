// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/Singleton.h"

class LittleWolf;
class Networking;

class Game : public Singleton<Game> {
	friend Singleton<Game>;
public:
	Game();
	virtual ~Game();
	bool init(const char* host, int port);
	void start();

	LittleWolf* getLittleWolf();
	Networking* getNetworking();

	//static Game* _instance;
	//static Game* instance() { return _instance; };

private:
	LittleWolf* little_wolf_;
	Networking* network_;

};

