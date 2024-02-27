// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "AsteroidsFacade.h"

class Vector2D;
class RandomNumberGenerator;

class AsteroidsUtils: public AsteroidsFacade {
public:
	AsteroidsUtils();
	virtual ~AsteroidsUtils();
	void remove_all_asteroids() override;
	void create_asteroids(int n) override;
	void split_astroid(ecs::entity_t a) override;

private:
	void generateAsteroid(const Vector2D &p, const Vector2D &v, int g);
	RandomNumberGenerator &rand_;
	int width_;
	int height_;

};

