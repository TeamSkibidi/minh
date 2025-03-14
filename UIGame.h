#pragma once


#include <SFML/Graphics.hpp>


class DashBoard;
class GridGame;


class UIGame {
private:
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	DashBoard* dashboard;
	GridGame* grid;
	
	sf::Event event;
	sf::View view;
	
	sf::Clock clock;
	double starting = 0.0001;

	void checkFPS();
	void initDashBoard();
	void initGrid();

public:
	UIGame(sf::RenderWindow* window);
	~UIGame();


	const bool running() const;


	void pollevent();
	void update();
	void render();
};
