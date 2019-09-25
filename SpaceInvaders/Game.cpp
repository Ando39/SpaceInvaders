#include "Game.h"

Game::Game(size_t wid, size_t hei, size_t enemiesToWin) : width(wid), height(hei),
									 window(sf::VideoMode(width, height), "My game"), counter(0), enemiesToWin(enemiesToWin),
									 textures(initTextures()), enemies(), fireworks(), state(State::WELCOME),
									 player(&textures["player"], &textures["bullet"], &textures["explosion"], (float)hei)
{
	srand((unsigned)time(0));
	initSprites();
}

std::map<std::string, sf::Texture> Game::initTextures() {
	
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> images{ "background.png", "player.png", "enemy.png", "bullet.png", "enemyBullet.png", "explosion.png" };

	for (auto const& value : images) {
		sf::Texture t;
		if (!t.loadFromFile("images/" + value)) throw std::invalid_argument("invalid texture");
		textures[value.substr(0, value.find(".", 0))] = t;
	}

	return textures;
}

void Game::initSprites() {

	background = sf::Sprite(textures["background"]);

	auto winSize = window.getSize();
	auto bckSize = textures["background"].getSize();
	float scaleX = (float)winSize.x / bckSize.x;
	float scaleY = (float)winSize.y / bckSize.y;

	background.setScale(sf::Vector2f(scaleX, scaleY));
}

void Game::updatePlayer() {
	sf::Vector2i mousepos = sf::Mouse::getPosition(window);

	mousepos.x -= player.width / 2;
	mousepos.y -= player.height / 2;
	float shipposx = (float)std::min((int)width - (int)player.width, std::max(0, mousepos.x));
	float shipposy = (float)std::min((int)height - (int)player.height, std::max(0, mousepos.y));

	player.setPosition(shipposx, shipposy);
	player.update();

}

void Game::updateEnemies(sf::Clock& timer) {

	for (Enemy& e : enemies) e.update();
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy e) { return e.y > height; }), enemies.end());

	if (timer.getElapsedTime().asSeconds() >= 1.5f) {

		float enemyx = (float)(std::rand() % (width - textures["enemy"].getSize().x));
		Enemy enemy(&textures["enemy"], &textures["enemyBullet"], &textures["explosion"], (float)height);
		enemy.setPosition(enemyx, (-1.0f) * (float)textures["enemy"].getSize().y);
		enemy.sprite.setPosition(enemyx, (-1.0f) * (float)textures["enemy"].getSize().y);
		enemies.push_back(enemy);
		timer.restart();

	}

}

void Game::drawPlayer() {

	for (auto const& bul : player.bullets)
		window.draw(bul.sprite);

	window.draw(player.sprite);
	if (player.state == Ship::State::EXPLOSION) window.draw(player.explosion.sprite);

}

void Game::drawEnemies() {
	for (auto const& enemy : enemies)
	{
		for (auto const& bul : enemy.bullets) window.draw(bul.sprite);
		window.draw(enemy.sprite);
		if (enemy.state == Ship::State::EXPLOSION) window.draw(enemy.explosion.sprite);
	}
}

void Game::drawFireworks(sf::Clock& fwTimer, sf::RectangleShape& rs) {

	if (fwTimer.getElapsedTime().asSeconds() >= 0.01f) {

		if (fireworks.empty()) {
			fireworks.push_back(Firework(sf::Color(255, 0, 0), 50, width, height));
			fireworks.push_back(Firework(sf::Color(0, 255, 0), 50, width, height));
			fireworks.push_back(Firework(sf::Color(0, 0, 255), 50, width, height));
		}

		fireworks.erase(std::remove_if(fireworks.begin(), fireworks.end(),
			[&](Firework& f) { return !f.explode(); }), fireworks.end());

		fwTimer.restart();
	}

	for (Firework const& f : fireworks)
		for (auto const& spark : f.sparks) {
			float fade = 1.0 - (f.age / 100.0);
			rs.setPosition(spark.x, spark.y);
			rs.setFillColor(sf::Color(spark.color.r * fade, spark.color.g * fade, spark.color.b * fade));
			window.draw(rs);
		}
}


void Game::checkForCollisions() {

	if (player.state == Ship::State::DESTROYED) state = State::END_LOST;
	if (counter == enemiesToWin) state = State::END_WIN;

	for (Enemy& e : enemies)
		if (player.checkForCollisions(e)) {
			state = State::END_LOST;
			return;
		}

	for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {

		if (it->state == Ship::State::HIT) ++counter;

		if (it->checkForCollisions(player)) {
			it = enemies.erase(it);
		}
		else ++it;

	}
}

void Game::start() {
	sf::Clock newEnemyTimer;
	sf::Clock fwTimer;

	sf::Vector2f boxSize(500, 200);
	sf::Font myFont;
	myFont.loadFromFile("myfont.ttf");

	sf::Text txt;
	txt.setFont(myFont);
	txt.setCharacterSize(30);
	txt.setPosition((width - boxSize.x) / 2, (height - boxSize.y) / 2);

	sf::Text counterTxt;
	counterTxt.setFont(myFont);
	counterTxt.setCharacterSize(40);
	counterTxt.setPosition(width - 100, 10);
	
	std::string welcomeStr = "Control ship with your mouse \n\n  Kill " + std::to_string(enemiesToWin) + " enemies to win \n\n  Press any key to start.";
	std::string lostStr = "         GAME OVER! \n\n  Press any key to end...";
	std::string winStr = "	CONGRATULATIONS!!! \n\n You killed all enemies!";

	window.setMouseCursorVisible(false);

	sf::RectangleShape rs(sf::Vector2f(4, 4));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
				if (state == State::WELCOME) state = State::GAME;
				else if (state == State::END_WIN || state == State::END_LOST) window.close();
		}


		if (state != State::GAME) {
			window.clear(sf::Color::White);
			window.draw(background);
			
			if (state == State::WELCOME) txt.setString(welcomeStr);
			else if (state == State::END_LOST) txt.setString(lostStr);
			if (state == State::END_WIN) {
				txt.setString(winStr);
				drawFireworks(fwTimer, rs);
			}
			else window.draw(counterTxt);

			window.draw(txt);
			
			window.display();
			continue;
		}

		updatePlayer();
		updateEnemies(newEnemyTimer);

		window.clear(sf::Color::White);
		window.draw(background);

		drawPlayer();
		drawEnemies();

		checkForCollisions();

		counterTxt.setString(std::to_string(counter));
		window.draw(counterTxt);

		window.display();
	}
}