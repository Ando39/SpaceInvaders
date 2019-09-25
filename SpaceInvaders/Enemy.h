#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Bullet.h"
#include "Ship.h"

class Enemy : public Ship {
private:
	sf::Clock move_timer;

public:
	Enemy(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height);

	virtual void update() override;
	virtual bool checkForCollisions(Ship&) override;
};