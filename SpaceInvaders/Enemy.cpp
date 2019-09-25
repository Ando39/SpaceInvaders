#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height) :
	Ship(texture, bullet_texture, explosion_texture, board_height), move_timer() {}


void Enemy::update() {

	if (y > maxy) return;

	if (bullets_move_timer.getElapsedTime().asMilliseconds() >= 2.0f) {
		updateBullets(Direction::DOWN);
		bullets_move_timer.restart();
	}

	if (state == State::EXPLOSION) {
		explode();
		return;
	}

	if (move_timer.getElapsedTime().asMilliseconds() >= 8.0f) {
		y += 1;
		sprite.setPosition(x, y);
		move_timer.restart();
	}

	if (shot_timer.getElapsedTime().asSeconds() >= 2.0f) {
		bullets.push_back(Bullet(bullet_texture, x + width / 2 - 10.0f, y + height / 2));
		shot_timer.restart();
	}
}

bool Enemy::checkForCollisions(Ship& player) {

	if (state == State::EXPLOSION) return false;
	if (state == State::HIT) state = State::EXPLOSION;

	if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {

		state = State::EXPLOSION;
		explosion.setPosition(x - 20.0f, y - 20.0f);

		return false;

	}

	std::list<Bullet>& bull = player.bullets;

	for (std::list<Bullet>::iterator it = bull.begin(); it != bull.end();)
		if (it->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
			bull.erase(it);
			state = State::HIT;
			explosion.setPosition(x - 20.0f, y - 20.0f);
			return false;
		}
		else ++it;

	if (state == State::DESTROYED) return true;

	return false;

}