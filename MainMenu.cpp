#include "MainMenu.h"
#include <iostream>

void MainMenu::initFont() {
	if (!this->font.loadFromFile("Dosis-VariableFont_wght.ttf")) {
		std::cout << "Cannot load font!" << std::endl;
	}
}

void MainMenu::initTitle()
{
	this->title.setFont(this->font);
	this->title.setString("2048");
	this->title.setCharacterSize(73);
	this->title.setFillColor(sf::Color(90, 80, 70));
	this->title.setPosition(200.f, 50.f);
}

void MainMenu::initAllButton()
{
	this->initButton(0, { 150.f, 200.f }, sf::Color::Red, "Classic Mode");
	this->initButton(1, { 150.f, 280.f }, sf::Color::Blue, "Time trial");
	this->initButton(2, { 150.f, 360.f }, sf::Color::Green, "How to play");
	this->initButton(3, { 150.f, 440.f }, sf::Color::Yellow, "Error");

}

void MainMenu::initButton(int index, sf::Vector2f pos, sf::Color color, std::string text)
{
	//Khởi tạo một cái khung có kích thước, màu khung và vị trí
	this->buttons[index].setSize(sf::Vector2f(300.f, 50.f));
	this->buttons[index].setFillColor(color);
	this->buttons[index].setPosition(pos);

	//Chữ trên cái khung
	this->buttonTexts[index].setFont(this->font);
	this->buttonTexts[index].setString(text);
	this->buttonTexts[index].setCharacterSize(24);
	this->buttonTexts[index].setFillColor(sf::Color::White);

	//Canh chữ ở giữa nút
	sf::FloatRect textBounds = this->buttonTexts[index].getLocalBounds();

	//Lấy vị trí chữ
	float textX = pos.x + (300.f - textBounds.width) / 2; //Căn ngang
	float textY = pos.y + (50.f - textBounds.height) / 2; //Căn dọc

	this->buttonTexts[index].setPosition(textX, textY);
	
}

MainMenu::MainMenu(sf::RenderWindow* window)
{
	this->window = window;
	this->initFont();
	this->initTitle();
	this->initAllButton();
	
}

void MainMenu::handleEvent(sf::Event event, GameState& state)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));


		for (int i = 0; i < 4; i++)
		{
			if (this->buttons[i].getGlobalBounds().contains(mousePos))
				switch (i)
				{
				case 0:
					state = GameState::PLAYING;
					break;
				case 1:
					state = GameState::TIME_TRIAL;
					break;
				case 2:
					state = GameState::HOW_TO_PLAY;
					break;
				case 3:
					state = GameState::EXIT;
					break;
				}
		}

	}
}

void MainMenu::render()
{
	this->window->draw(this->title);

	for (int i = 0; i < 4; i++)
	{
		this->window->draw(this->buttons[i]);
		this->window->draw(this->buttonTexts[i]);
	}

}


