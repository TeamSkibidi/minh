#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "MainMenu.h"
#include "GameState.h"
#include "UIGame.h"
#include "Game_Functions.h"
#include "DashBoard.h"



class Game
{
private:
	//quản
	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	

	DashBoard* dashboard;
	MainMenu* mainMenu;
	UIGame* uiGame;
	GameState gameState;
	Game_Functions GameFunction;


	sf::Event event;
	
	//Game object
	
	void initWindow();
	void initMainMenu();
	
public:
	//Constructors and Destructor
	Game();
	~Game();
	


	//Functions
	const bool running() const;

	
	void pollEvents();
	void updateGameState();
	void updateGamefunction();
	//void updatePollevent();
	void update();
	void render();
	Game_Functions& getFunction() {
		return GameFunction;
	}
};


