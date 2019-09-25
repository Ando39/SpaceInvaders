#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
	sf::Sprite sprite;
	float x, y;

	Bullet(sf::Texture* bull, float x, float y) : x(x), y(y), sprite(*bull) {
		sprite.setScale(0.4f, 0.4f);
		sprite.setPosition(x, y);
	}

	void move(int count) {
		y += count;
		sprite.setPosition(x, y);
	}

};