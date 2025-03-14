#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;

class DashBoard {
private:
	sf::RenderWindow* window;
	sf::RectangleShape rec[6];
	sf::Text newText[3];

	sf::Font font;

	sf::Sprite newSprite[4];
	sf::Texture textures[4];


	void initRectangle(int index, float x, float y, sf::Color color, float sizeWidth, float sizeHight);
	void initAllRec();


	void initText(int index, sf::Font font, string text, int size, float x, float y, sf::Color color);
	void initAllText();

	void initPng(int index, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);
	void initAllimage();

public:
	DashBoard(sf::RenderWindow* window);

	void initFont(sf::Font& font);
	void presssEvent(sf::Event event);
	void render();

};