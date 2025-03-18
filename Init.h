#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Init
{
public:
	void initRectangle(sf::RectangleShape &rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight);
	void initText(sf::Text& newText,const sf::Font &font, const string &text, int size, float x, float y, sf::Color color);
	void initPng(sf::Texture& textures, sf::Sprite &newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);
};

