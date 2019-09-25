#include "Player.h"

Player::Player(sf::Texture* texture, sf::Texture* bullet_texture, sf::Texture* explosion_texture, float board_height) :
	Ship(texture, bullet_texture, explosion_texture, board_height) {}

void Player::update()
{

	if (bullets_move_timer.getElapsedTime().asMilliseconds() >= 1.5f) {
		updateBullets(Direction::UP);
		bullets_move_timer.restart();
	}

	if (state == State::EXPLOSION) {
		explode();
		return;
	}

	sprite.setPosition(x, y);

	if (shot_timer.getElapsedTime().asSeconds() >= 1.0f) {
		bullets.push_back(Bullet(bullet_texture, x - 3.0f, y + 35.0f));
		bullets.push_back(Bullet(bullet_texture, x + width - 15.0f, y + 35.0f));
		shot_timer.restart();
	}

}

bool Player::checkForCollisions(Ship& ship)
{
	if (state == State::DESTROYED) return true;
	if (state == State::EXPLOSION) return false;

	Enemy const& e = (Enemy&)ship;
	if (e.state != State::EXPLOSION && e.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {

		state = State::EXPLOSION;
		explosion.setPosition(x - 20.0f, y - height / 2);

		return false;

	}

	for (const Bullet &b : e.bullets)
		if (b.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {

			state = State::EXPLOSION;
			explosion.setPosition(x - 20.0f, y - height / 2);
			return false;

		}

	return false;

}