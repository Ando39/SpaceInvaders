#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Firework.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"

class Game {
public:
	enum State { WELCOME, GAME, END_WIN, END_LOST };

private:
	size_t width, height;
	sf::RenderWindow window;
	std::map<std::string, sf::Texture> textures;
	sf::Sprite background;
	Player player;
	std::list<Enemy> enemies;
	std::vector<Firework> fireworks;
	State state;
	size_t counter, enemiesToWin;

	void updatePlayer();
	void updateEnemies(sf::Clock&);
	void drawPlayer();
	void drawEnemies();
	void drawFireworks(sf::Clock&, sf::RectangleShape&); // if player wins (enemiesToWin == counter)

	void checkForCollisions();

public:
	Game(size_t, size_t, size_t);
	void start();
	std::map<std::string, sf::Texture> initTextures(); // load game textures by name
	void initSprites();

};