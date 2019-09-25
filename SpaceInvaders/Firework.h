#pragma once
#include <SFML/Graphics.hpp>
#include "Spark.h"

#define random_float ((float)rand() / RAND_MAX)

class Firework {
public:
	float x, y;
	std::vector<Spark> sparks;
	sf::Color color;
	size_t maxSparks, age, size;
	float maxWidth, maxHeight;

	Firework(sf::Color color, size_t maxSparks, size_t maxWidth, size_t maxHeight);

	bool explode();

};