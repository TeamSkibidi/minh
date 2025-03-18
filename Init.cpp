#include "Init.h"
#include <iostream>

using namespace std;

void Init::initRectangle(sf::RectangleShape& rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight)
{
	rec.setSize(sf::Vector2f(sizeWidth, sizeHight));
	rec.setFillColor(color);
	rec.setPosition(x, y);
}



void Init::initText(sf::Text& newText,const sf::Font &font, const string &text, int size, float x, float y, sf::Color color)
{
	newText.setFont(font);
	newText.setString(text);
	newText.setCharacterSize(size);
	newText.setFillColor(color);
	newText.setPosition(x, y);
}

void Init::initPng(sf::Texture &textures, sf::Sprite &newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{
	if (!textures.loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	newSprite.setTexture(textures);
	newSprite.setScale(sizeX, sizeY);
	newSprite.setPosition(x, y);
	newSprite.setColor(color);
}
