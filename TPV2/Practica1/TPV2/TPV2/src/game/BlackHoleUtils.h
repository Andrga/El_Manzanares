#pragma once
#include "BlackHoleFacade.h"

class Vector2D;
class RandomNumberGenerator;

const int RAD_MIN = 100;

class BlackHoleUtils : public BlackHoleFacade
{
public:
	BlackHoleUtils();
	virtual ~BlackHoleUtils();
	void create_blackholes(int n) override;
	void remove_all_blackholes() override;

private:
	//void generateBlackHole(const Vector2D& p, const Vector2D& v, int g);
	RandomNumberGenerator& rand_;
	ecs::Manager* mngr_;
};

