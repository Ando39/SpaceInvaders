#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Game.h"

int main()
{
	Game game(1200, 800, 5); // changed last argument (enemiesToWin) for faster win

	try { 
		game.start();
	}
	catch (const std::invalid_argument&) {
		MessageBox(NULL, "Something went wrong.", "Game error", MB_OK);
	}
	return 0;
}