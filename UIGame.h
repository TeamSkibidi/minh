#pragma once


#include <SFML/Graphics.hpp>
#include "Game_Functions.h"
#include "MainMenu.h"
#include "GameState.h"
class DashBoard;
class GridGame;


class UIGame {
private:
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	DashBoard* dashboard;
	GridGame* grid;
	MainMenu* mainMenu;
	
	Game_Functions& GameFunction;
	GameState gameState;
	sf::Event event;
	sf::View view;
	
	sf::Clock clock;
	double starting = 0.0001;

	void checkFPS();
	void initDashBoard();
	void initGrid();

public:
	UIGame(sf::RenderWindow* window, Game_Functions& GF);
	~UIGame();


	const bool running() const;

	void updateWindow();
	void pollevent();
	void updatePollevent();
	void update();
	void render();
	
};
