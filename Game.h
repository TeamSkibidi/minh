#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "MainMenu.h"
#include "GameState.h"

class MainMenu;

class Game
{
private:
	//quản
	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	GameState gameState;

	MainMenu* mainMenu;


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
	void update();
	void render();


};


