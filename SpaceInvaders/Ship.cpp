#include "Ship.h"
#include <iostream>

Ship::Ship(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height) :
	bullets(), x(x), y(y), sprite(*texture), explosion(explosion_texture), state(ACTIVE), maxy(board_height), bullets_move_timer(), shot_timer()
{
	
	width = texture->getSize().x;
	height = texture->getSize().y;
	this->bullet_texture = bullet_texture;

}

void Ship::setPosition(float x, float y) { this->x = x; this->y = y; }

void Ship::updateBullets(Direction dir) {
	bool is_up = dir == Direction::UP;
	for (auto& bullet : bullets) bullet.move(is_up ? -1 : 1);
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](Bullet b) { return is_up ? b.y < 0 : b.y > maxy; }), bullets.end());
}

void Ship::explode() {
	if (explosion.makeExplosion() && bullets.empty()) state = State::DESTROYED;
}