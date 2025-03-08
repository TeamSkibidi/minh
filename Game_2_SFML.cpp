#include <iostream>
#include "Game.h"

int main()
{

	std::srand(static_cast<unsigned>(time(nullptr)));

	//Initilize game object
	Game game;

	//Game loop
	while (game.running()) {

		game.update();

		game.render();
	}
	//End of application



}
