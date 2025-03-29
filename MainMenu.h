#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "GameState.h"



class MainMenu
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text title;

	sf::RectangleShape buttons[4];
	sf::Text buttonTexts[4];


	void initFont();
	void initTitle();
	void initAllButton();
	void initButton(int index, sf::Vector2f pos, sf::Color color, std::string text);
public:

	MainMenu(sf::RenderWindow* window);
	void handleEvent(sf::Event event, GameState& state);
	void render();	
		
};

