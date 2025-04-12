#include "Init.h"
#include <iostream>

using namespace std;

void Init::initRectangle(sf::RectangleShape& rec, float x, float y, sf::Color color, float sizeWidth, float sizeHight)
{
	rec.setSize(sf::Vector2f(sizeWidth, sizeHight));
	rec.setFillColor(color);
	rec.setPosition(x, y);
}



void Init::initText(sf::Text& newText, const sf::Font& font, int size, float x, float y, sf::Color color, const string& text)
{
	newText.setFont(font);
	newText.setString(text);
	newText.setCharacterSize(size);
	newText.setFillColor(color);
	newText.setPosition(x, y);
}

void Init::centerTextInRect(sf::Text& text, const sf::RectangleShape& rect)
{
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getSize();

	// Đặt origin về tâm chữ (center)
	text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);

	// Đặt lại vị trí để nằm giữa rec
	text.setPosition(rectPos.x + rectSize.x / 2.0f,
		rectPos.y + rectSize.y / 2.0f);
}

void Init::alignTextLeftCenterY(sf::Text& text, const sf::RectangleShape& rect, float paddingLeft)
{
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getSize();

	// Đặt origin trái và căn giữa theo chiều cao
	text.setOrigin(textBounds.left, textBounds.height / 2.f);

	// Đặt vị trí text: trái có padding, giữa theo y
	text.setPosition(rectPos.x + paddingLeft, rectPos.y + rectSize.y / 2.f);
}

void Init::setInputTextPosition(sf::Text& text, const sf::RectangleShape& rect, float paddingLeft, float paddingTop)
{
	sf::Vector2f rectPos = rect.getPosition();
	text.setPosition(rectPos.x + paddingLeft, rectPos.y + paddingTop);
}



void Init::initPng(sf::Texture& textures, sf::Sprite& newSprite, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{
	if (!textures.loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	cout << "AAAAAAAAAAAAAA";
	newSprite.setTexture(textures);
	newSprite.setScale(sizeX, sizeY);
	newSprite.setPosition(x, y);
	newSprite.setColor(color);
}
