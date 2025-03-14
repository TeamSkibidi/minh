#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "UIGame.h"
#include "DashBoard.h"
#include "ColorGame.h"


class GridGame {
private:
	vector<vector<int>> BoardGame;
	sf::RenderWindow* window;
	sf::RectangleShape shape;
	sf::Font font;


	void initFont();
	void createGridGame();

public:

	GridGame(sf::RenderWindow* window);
	void RenderGridGame();

};
