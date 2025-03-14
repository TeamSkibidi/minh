#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "UIGame.h"
#include "DashBoard.h"
#include "Grid.h"


void UIGame::checkFPS()
{

	this->window->setFramerateLimit(60);
	double ending = clock.getElapsedTime().asSeconds();
	double timeFPS = ending - starting;
	string FPS;

	if (timeFPS > 0.0001) {
		FPS = to_string(int(1.0 / timeFPS));
	}
	this->window->setTitle("2048 FPS: " + FPS);
	this->starting = ending;
}

void UIGame::initDashBoard()
{
	this->dashboard = new DashBoard(this->window);
}

void UIGame::initGrid()
{
	this->grid = new GridGame(this->window);
}

UIGame::UIGame(sf::RenderWindow* window)
{
	this->window = window;
	this->initDashBoard();
	this->initGrid();
}


UIGame::~UIGame()
{
	delete this->dashboard;
	delete this->grid;
	this->dashboard = nullptr;
	this->grid = nullptr;

}


const bool UIGame::running() const
{
	return this->window->isOpen();
}


void UIGame::pollevent()
{
	if (!this->window) return;


	this->view = sf::View(sf::FloatRect(0, 0, 600, 800));

	while (this->window->pollEvent(event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
		else if (this->event.type == sf::Event::Resized) {
			float Update_width = static_cast<float>(this->event.size.width);
			float Update_height = static_cast<float>(this->event.size.height);

			float Update_board = Update_width / Update_height;
			float board = 600.0f / 800.0f;

			if (Update_board > board) {
				this->view.setSize(static_cast <float>(800 * Update_board), static_cast <float>(800));
			}
			else {
				this->view.setSize(static_cast <float>(600), static_cast <float>(600 / Update_board));
			}
			this->window->setView(view);
		}
	}
}

void UIGame::update()
{
	this->pollevent();
}

void UIGame::render()
{
	checkFPS();
	if (!this->window)
		return;

	/*this->window->clear(sf::Color(245, 243, 227));*/
	this->dashboard->render();
	this->grid->RenderGridGame();

}




