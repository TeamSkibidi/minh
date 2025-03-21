#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "UIGame.h"
#include "DashBoard.h"
#include "GridGame.h"
#include "Game.h"
#include "GameLogic.h"

// Measure game FPS
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

// Constructor and destructor Game UI
UIGame::UIGame(sf::RenderWindow* window, Game_Functions& GF) : GameFunction(GF) {
	this->window = window;
	this->initDashBoard();
	this->initGrid();
	this->update();
	/*this->GameFunction = Game_Functions::GAMECLASSIC;*/

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


void UIGame::updateWindow()
{
	this->view = sf::View(sf::FloatRect(0, 0, 600, 800));

	if (this->event.type == sf::Event::Resized)
	{
		// Get size window new
		float Update_width = static_cast<float>(this->event.size.width);
		float Update_height = static_cast<float>(this->event.size.height);

		// Get the new window scale
		float Update_board = Update_width / Update_height;

		// Get window scale
		float board = 600.0f / 800.0f;

		// Update size the new window
		if (Update_board > board) {
			this->view.setSize(static_cast <float>(800 * Update_board), static_cast <float>(800));
		}
		else {
			this->view.setSize(static_cast <float>(600), static_cast <float>(600 / Update_board));
		}
		this->window->setView(view);
	}

}

void UIGame::pollevent()
{
	if (!this->window) return;

	while (this->window->pollEvent(event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
		// Check for window changes
		this->updateWindow();

		// Detect mouse button click 
		if (this->GameFunction == Game_Functions::GAMECLASSIC) {
			this->dashboard->pressdFuncion(event, this->GameFunction);
			std::cout << "dmm";
		}
		std::cout << "z";

		if (this->event.type == sf::Event::KeyPressed) {
			bool moved = false;
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
				goup(*this->grid);
				moved = true;
				break;
			case sf::Keyboard::Down:
				godown(*this->grid);
				moved = true;
				break;
			case sf::Keyboard::Left:
				turnleft(*this->grid);
				moved = true;
				break;
			case sf::Keyboard::Right:
				turnright(*this->grid);
				moved = true;
				break;
			default:
				break;
			}
			if (moved) {
				random_pos(this->grid->getBoardGame());
			}
		}
	}
}

void UIGame::updatePollevent()
{
	if (this->GameFunction == Game_Functions::HOME) {
		this->GameFunction = Game_Functions::DELETEGAME;
	}
}

void UIGame::update()
{
	this->pollevent();
	this->updatePollevent();
}


// Render game UI including dashboard and grid
void UIGame::render()
{
	checkFPS();
	if (!this->window)
		return;

	if (this->GameFunction == Game_Functions::HOME) {
		this->mainMenu->render();
	}
	else if (this->GameFunction == Game_Functions::GAMECLASSIC) {
		this->dashboard->render();
		this->grid->RenderGridGame();
	}


}




