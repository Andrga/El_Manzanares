
#include "IG1App.h"
#include <iostream>

#ifdef WIN32
#include <windows.h>

int
ctrl_handler(int event) // callback
{
	if (event == CTRL_CLOSE_EVENT) { // when the user closes the console
		IG1App::s_ig1app.close();
		return 1;
	} else
		return 0;
}
#endif

int
main(int argc, char* argv[])
{
#ifdef WIN32
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), 1); // callback registration
	SetConsoleOutputCP(CP_UTF8);                                // console output in UTF-8
#endif

	try {
		std::cout << "Starting application...\n";
		IG1App::s_ig1app.run();
		std::cout << "Closing application...\n";
	} catch (std::exception& e) {
		std::cout << e.what() << '\n';
		std::cin.ignore(INT_MAX, '\n');
	} catch (...) {
		std::cout << "ERROR: Closing application...\n";
		std::cin.ignore(INT_MAX, '\n');
	};

	return 0;
}
