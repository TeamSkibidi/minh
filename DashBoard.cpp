#include "DashBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "game.h"

using namespace std;
void DashBoard::initFont(sf::Font& font) {
	font.loadFromFile("Dosis-VariableFont_wght.ttf");
}
void DashBoard::initRectangle(int index, float x, float y, sf::Color color, float sizeWidth, float sizeHight)
{

	this->rec[index].setSize(sf::Vector2f(sizeWidth, sizeHight));
	this->rec[index].setFillColor(color);
	this->rec[index].setPosition(x, y);
}
void DashBoard::initText(int index, sf::Font font, string text, int size, float x, float y, sf::Color color)
{

	this->newText[index].setFont(this->font);
	this->newText[index].setString(text);
	this->newText[index].setCharacterSize(size);
	this->newText[index].setFillColor(color);
	this->newText[index].setPosition(x, y);
}

void DashBoard::initPng(int index, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color)
{

	if (!this->textures[index].loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	this->newSprite[index].setTexture(this->textures[index]);
	this->newSprite[index].setScale(sizeX, sizeY);
	this->newSprite[index].setPosition(x, y);
	this->newSprite[index].setColor(color);
}
void DashBoard::initAllRec()
{
	this->initRectangle(0, 280, 100, sf::Color(245, 149, 99), 100, 70);
	this->initRectangle(1, 395, 100, sf::Color(245, 149, 99), 145, 70);
	this->initRectangle(2, 435, 200, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(3, 480, 200, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(4, 135, 200, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(5, 90, 200, sf::Color(187, 173, 160), 40, 40);
}
void DashBoard::initAllimage()
{
	this->initPng(0, "Undo.png", 431, 198, 0.2f, 0.2f, sf::Color::White);
	this->initPng(1, "Redo.png", 476, 198, 0.2f, 0.2f, sf::Color::White);
	this->initPng(2, "Refresh.jpg", 141, 206, 0.11f, 0.11f, sf::Color::White);
	this->initPng(3, "Home.png", 90, 201, 0.4f, 0.4f, sf::Color::White);

}

void DashBoard::initAllText()
{

	this->initText(0, font, "2048", 70, 100, 90, sf::Color(187, 173, 160));
	this->initText(1, font, "Score", 25, 295, 110, sf::Color::White);
	this->initText(2, font, "Best Score", 25, 405, 110, sf::Color::White);
}

DashBoard::DashBoard(sf::RenderWindow* window)
{
	this->window = window;
	this->initFont(this->font);
	this->initAllRec();
	this->initAllimage();
	this->initAllText();
}

void DashBoard::presssEvent(sf::Event event)
{
}

void DashBoard::render()
{
	if (!this->window) {
		std::cerr << "Error: `window` is null in DashBoard::render()!" << std::endl;
		return;
	}

	for (int j = 0; j < 6; j++) {
		this->window->draw(this->rec[j]);
	}

	for (int i = 0; i < 4; i++) {
		if (i < 3) {
			this->window->draw(this->newText[i]);
		}
		if (i < 4) {
			this->window->draw(this->newSprite[i]);
		}
	}

}