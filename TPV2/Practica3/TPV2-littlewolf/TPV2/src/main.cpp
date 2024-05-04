// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <fstream>

#include "game/Game.h"
#include "game/UDPServer.h"

#include "sdlutils/SDLNetUtils.h"

void server(Uint16 port) {

}

void client(const char* host, Uint16 port) {
	Game g;

	g.init(host, port);
	g.start();
}

int main(int, char**) {

	try {
		sdlUtils
		const char* host;

	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 66;
}

