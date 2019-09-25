#pragma once
#include <SFML/Graphics.hpp>

#define random_float ((float)rand() / RAND_MAX)

class Spark {
public:
	float defx, defy, x, y, weight;
	sf::Color color;

	Spark(float defx, float defy, float x, float y, float weight, sf::Color color) 
		: defx(x), defy(y), x(x), y(y), weight(weight) {
	
		if (color.r == 255) this->color = sf::Color(255, random_float * 255, random_float * 255);
		else if (color.g == 255) this->color = sf::Color(random_float * 255, 255, random_float * 255);
		else if (color.b == 255) this->color = sf::Color(random_float * 255, random_float * 255, 255);
		
	}
};