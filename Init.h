#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Init
{
public:
	void initRectangle(sf::RectangleShape& rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight);
	void initText(sf::Text& newText, const sf::Font& font, int size, float x, float y, sf::Color color, const string& text);
	void centerTextInRect(sf::Text& text, const sf::RectangleShape& rect);
	void alignTextLeftCenterY(sf::Text& text, const sf::RectangleShape& rect, float paddingLeft = 10.f);
	void setInputTextPosition(sf::Text& text, const sf::RectangleShape& rect, float paddingLeft, float paddingTop);
	void initPng(sf::Texture& textures, sf::Sprite& newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color);
};

