#pragma once
#include <list>
#include "Bullet.h"
#include "Explosion.h"

// abstract class
class Ship {
public:
	enum State { ACTIVE, HIT, EXPLOSION, DESTROYED };
	enum Direction { UP, DOWN };
	
	float x, y;
	State state;
	sf::Sprite sprite;
	Explosion explosion;
	size_t width, height;
	std::list<Bullet> bullets;

	Ship(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height);
	
	void setPosition(float x, float y);

	virtual void update() = 0;
	virtual bool checkForCollisions(Ship& ship) = 0;

protected:
	float maxy;
	sf::Texture* bullet_texture;
	sf::Clock bullets_move_timer, shot_timer;


	void updateBullets(Direction dir);
	void explode();

};