#include "Game.h"


void Game::initWindow()
{
	this->videoMode = sf::VideoMode(600, 800);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Titlebar | sf::Style::Close);
    this->gameState = GameState::MAIN_MENU;
   
}

void Game::initMainMenu()
{
    this->mainMenu = new MainMenu(this->window);
    this->uiGame = nullptr;
}


//Constructor and destructor
Game::Game()
{
    this->initWindow();
    this->initMainMenu();
    
    
}

Game::~Game()
{

    delete this->mainMenu;
    this->mainMenu = nullptr;
    
    delete this->window;
    this->window = nullptr; // Tránh trỏ vào vùng nhớ không hợp lệ

    delete this->uiGame;
    this->uiGame = nullptr;
}

//Functions

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{

    if (!this->window) return;

    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }

        if (this->gameState == GameState::MAIN_MENU)
        {
            this->mainMenu->handleEvent(event, this->gameState);
        }
        
        
    }
}

void Game::updateGameState()
{

    if (this->gameState == GameState::PLAYING)
    {
        if (this->uiGame == nullptr)
        {
            delete this->mainMenu;
            this->mainMenu = nullptr;
            this->uiGame = new UIGame(this->window);
        }
        
    }
}

void Game::update()
{
    this->pollEvents();
    this->updateGameState();
}


void Game::render()
{

    if (!this->window) return;
    this->window->clear(sf::Color(239, 227, 203));

    if (this->gameState == GameState::MAIN_MENU && this->mainMenu)
    {
        this->mainMenu->render();
    }
    else if (this->gameState == GameState::PLAYING && this->uiGame)
    {
        this->uiGame->render();
    }
    else if (this->gameState == GameState::PLAYING && this->uiGame)
    {
        this->uiGame->render();

    }
    else if (this->gameState == GameState::PLAYING && this->uiGame)
    {
        this->uiGame->render();
    }
    this->window->display();
}




