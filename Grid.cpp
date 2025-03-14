#include "Grid.h"
#include <vector>
#include <SFML/Graphics.hpp>



using namespace std;
void GridGame::initFont()
{
	if (!this->font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		cout << "Error loading font!" << endl;
	}
}
void GridGame::createGridGame()
{
	this->BoardGame.clear();
	for (int i = 0; i < 4; i++) {
		vector<int> row;
		for (int j = 0; j < 4; j++) {
			row.push_back(0);
		}
		this->BoardGame.push_back(row);
	}
}



void GridGame::RenderGridGame()
{
	for (int i = 0; i < this->BoardGame[0].size(); i++) {
		for (int j = 0; j < this->BoardGame[0].size(); j++) {
			this->shape.setSize(sf::Vector2f(static_cast<float>(95), static_cast<float>(95)));
			this->shape.setPosition(static_cast<float>(j * 105 + 100), static_cast<float>(i * 105 + 265));
			this->shape.setFillColor(getColor(BoardGame[i][j]));
			this->shape.setOutlineThickness(10);
			this->shape.setOutlineColor(sf::Color(187, 173, 160));

			this->window->draw(shape);

			if (this->BoardGame[i][j] != 0) {
				sf::FloatRect textRect;
				sf::Text text;


				text.setFont(this->font);
				text.setString(to_string(BoardGame[i][j]));
				text.setCharacterSize(40);
				text.setFillColor(sf::Color::Black);

				sf::FloatRect textBounds = text.getGlobalBounds();
				text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
				text.setPosition(static_cast<float>(j * 105 + 135), static_cast<float>(i * 105 + 285));
				this->window->draw(text);
			}
		}
	}
}

GridGame::GridGame(sf::RenderWindow* window)
{

	this->window = window;
	this->initFont();
	if (this->BoardGame.empty()) {
		this->createGridGame();
	}
}


