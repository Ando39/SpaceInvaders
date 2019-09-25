#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
public: 
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;
	size_t explosion_number;
	sf::Clock explosion_timer;

	Explosion(sf::Texture* explosion) : 
		rectSourceSprite(0, 0, 128, 128), sprite(*explosion, rectSourceSprite), 
		explosion_timer(), explosion_number(0) {}

	void setPosition(float x, float y) { sprite.setPosition(x, y); }

	bool makeExplosion() {
		if (explosion_number > 63) return true;
		if (explosion_timer.getElapsedTime().asMilliseconds() < 20.0f) return false;

		int top = explosion_number / 8;
		int left = explosion_number % 8;

		sprite.setTextureRect(sf::IntRect(left * 128, top * 128, 128, 128));

		++explosion_number;

		explosion_timer.restart();

		return false;
	}

};