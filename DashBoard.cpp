#include "DashBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Game.h"

using namespace std;



void DashBoard::initFont(sf::Font& font) {
	font.loadFromFile("Dosis-VariableFont_wght.ttf");
}

// Include rectangle
void DashBoard::initRectangle(int index, sf::Vector2f pos, sf::Color color, float sizeWidth, float sizeHight)
{

	this->rec[index].setSize(sf::Vector2f(sizeWidth, sizeHight));
	this->rec[index].setFillColor(color);
	this->rec[index].setPosition(pos);
}

// Include text
void DashBoard::initText(int index, sf::Font font, string text, int size, float x, float y, sf::Color color)
{

	this->newText[index].setFont(this->font);
	this->newText[index].setString(text);
	this->newText[index].setCharacterSize(size);
	this->newText[index].setFillColor(color);
	this->newText[index].setPosition(x, y);
}

// Include image
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

// Initialize all rectangle displayed
void DashBoard::initAllRec()
{
	this->initRectangle(0, { 280.f, 100.f }, sf::Color(245, 149, 99), 100, 70);
	this->initRectangle(1, { 395.f, 100.f }, sf::Color(245, 149, 99), 145, 70);
	this->initRectangle(2, { 435.f, 200.f }, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(3, { 480.f, 200.f }, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(4, { 135.f, 200.f }, sf::Color(187, 173, 160), 40, 40);
	this->initRectangle(5, { 90.f, 200.f }, sf::Color(187, 173, 160), 40, 40);
}

// Initialize all image displayed
void DashBoard::initAllimage()
{
	this->initPng(0, "Undo.png", 423, 200, 0.2f, 0.2f, sf::Color::White);
	this->initPng(1, "Redo.png", 474, 200, 0.2f, 0.2f, sf::Color::White);
	this->initPng(2, "Refresh.jpg", 149, 207.5, 0.11f, 0.11f, sf::Color::White);
	this->initPng(3, "Home.png", 92, 202, 0.4f, 0.4f, sf::Color::White);
	this->initPng(4, "Square2.png", 425, 200, 0.08f, 0.08f, sf::Color(187, 173, 160));
	this->initPng(5, "Square2.png", 476, 200, 0.08f, 0.08f, sf::Color(187, 173, 160));
	this->initPng(6, "Square2.png", 141, 200, 0.08f, 0.08f, sf::Color(187, 173, 160));
	this->initPng(7, "Square2.png", 90, 200, 0.08f, 0.08f, sf::Color(187, 173, 160));
	this->initPng(8, "Square.png", 410, 100, 0.2f, 0.13f, sf::Color(245, 149, 99));
	this->initPng(9, "Square.png", 300, 100, 0.17f, 0.13f, sf::Color(245, 149, 99));
	this->initPng(10, "2048.png", 100, 100, 0.2f, 0.2f, sf::Color(187, 173, 160));
}

// Initialize all text displayed
void DashBoard::initAllText()
{
	//this->initText(0, font, "2048", 70, 100, 90, sf::Color(187, 173, 160));
	this->initText(0, font, "Score", 25, 320, 108, sf::Color::White);
	this->initText(1, font, "Best Score", 25, 419, 110, sf::Color::White);
}

// Include text, rectangle and image 
DashBoard::DashBoard(sf::RenderWindow* window)
{
	this->window = window;
	this->initFont(this->font);
	this->initAllRec();
	this->initAllimage();
	this->initAllText();
}

// Procces mouse button press
void DashBoard::pressdFuncion(sf::Event event, Game_Functions& gameFunctions)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		std::cout << "b";
		for (int i = 2; i < 6; i++) {
			sf::FloatRect bounds = rec[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				switch (i) {
				case 5:
					gameFunctions = Game_Functions::HOME;
					cout << "..................................";
					std::cout << ": " << static_cast<int>(gameFunctions) << "\n";
					break;
				case 4:
					gameFunctions = Game_Functions::REFRESH;
					cout << ".........3333.....................";
					break;

				case 3:
					gameFunctions = Game_Functions::REDO;
					cout << ".........444.....................";
					break;

				case 2:
					gameFunctions = Game_Functions::UNDO;
					cout << ".........555.....................";
					break;
				}
			}
		}
	}
}

// Render images and rectangle and text for dash board
void DashBoard::render()
{
	if (!this->window) {
		std::cerr << "Error: `window` is null in DashBoard::render()!" << std::endl;
		return;
	}

	for (int j = 0; j < 3; j++) {
		//this->window->draw(this->rec[j]);
	}

	for (int i = 10; i >= 0; i--) {
		if (i < 2) {
			this->window->draw(this->newText[i]);
		}
		this->window->draw(this->newSprite[i]);
	}
}
