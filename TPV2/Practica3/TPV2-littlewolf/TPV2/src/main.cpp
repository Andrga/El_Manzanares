// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <fstream>

#include "game/Game.h"
#include "game/UDPServer.h"

#include "sdlutils/SDLNetUtils.h"

void server(Uint16 port) {
	UDPServer s(port, 10);
	std::cout << "server" << std::endl;
}

void client(const char* host, Uint16 port) {
	Game& g = *Game::instance();

	std::cout << "client" << std::endl;

	if (g.init(host, port)) {
		g.start();
		std::cout << "start game" << std::endl;
	}
}

void start(int argc, char** argv) {
	SDLNetUtils::initSDLNet();
	std::cout << "Start" << std::endl;
	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(static_cast<Uint16>(atoi(argv[2]))); // start in server mode
	}
	else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], static_cast<Uint16>(atoi(argv[3]))); // start in client mode
	}
	else {
		std::cout << "Usage: " << std::endl;
		std::cout << "  " << argv[0] << " server port " << std::endl;
		std::cout << "  " << argv[0] << " client host port " << std::endl;
		std::cout << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "  " << argv[0] << " server 2000" << std::endl;
		std::cout << "  " << argv[0] << " client localhost 2000" << std::endl;
	}

	SDLNetUtils::closeSDLNet();
}

int main(int argc, char** argv) {

	try {
		std::cout << "main" << std::endl;
		start(argc, argv);
	}
	catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 66;
}

