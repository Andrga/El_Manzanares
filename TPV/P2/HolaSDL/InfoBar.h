#pragma once
#include "GameObject.h"

class InfoBar : public GameObject
{
private:
	int score;


public:

	InfoBar(int scr);

	~InfoBar();

	void update() override;

	void const render() override;

	void const save(ofstream& fil)override;
};

