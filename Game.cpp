#include "Game.h"
#include <iostream>


using namespace std;

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

    // Take Event
    while (this->window->pollEvent(event)) 
    {

        if (event.type == sf::Event::Closed) 
        {
            this->window->close();
        }

        // Programming a Game Menu
        if (this->gameState == GameState::MAIN_MENU)
        {
            this->mainMenu->handleEvent(event, this->gameState);
            cout << " NO ";
        }

        // Programming a Play Game Classic Mode
        if (this->GameFunction == Game_Functions::GAMECLASSIC) 
        {
            this->uiGame->update();
            cout << "L";
        }
    }
}


// Update Game Menu
void Game::updateGameState()
{
    if (this->gameState == GameState::PLAYING)
    {
        if (this->uiGame == nullptr)
        {
            // Delete window Menu and create window Game UI
            delete this->mainMenu;
            this->mainMenu = nullptr;
            this->uiGame = new UIGame(this->window, this->getFunction());
            this->GameFunction = Game_Functions::GAMECLASSIC;
            std::cout << "check";
        }
    }
   

}
// Update Game State Management
void Game::updateGamefunction() {
    if (this->GameFunction == Game_Functions::DELETEGAME && this->uiGame != nullptr)
    {
        // Delete window Game Ui and create window Menu
        delete this->uiGame;
        this->uiGame = nullptr;
        this->mainMenu = new MainMenu(this->window);
        this->gameState = GameState::MAIN_MENU;
        cout << "Check HOME";
    }
}


// Update Game Mode
void Game::update()
{
    if (this->mainMenu != nullptr) {
        this->pollEvents();
    }
    if (this->uiGame != nullptr) {
        this->uiGame->update();
        cout << " K ";
    }
    this->updateGamefunction();
    this->updateGameState();
    std::cout << "P";
}


// Render Game Mode
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
    this->window->display();
}




