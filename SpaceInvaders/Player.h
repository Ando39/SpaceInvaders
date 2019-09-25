#pragma once
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"

class Player : public Ship {
public:
	Player(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height);
	// Inherited via Ship
	virtual void update() override;
	virtual bool checkForCollisions(Ship&) override;
};