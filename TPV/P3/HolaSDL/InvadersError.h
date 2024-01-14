#pragma once
#include <stdexcept>
#include <string>

//using namespace std;

class InvadersError : public std::logic_error
{
private:
	std::string message;

public:

	InvadersError(const std::string& mes) : logic_error(mes), message(mes) {}
	char const* what() const override {	return message.c_str();}
};

