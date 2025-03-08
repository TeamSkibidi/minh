#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>


using namespace std;





sf::Color getColor(int val) {
	switch (val) {
	case 2:
		return sf::Color(238, 228, 218);
	case 4:
		return sf::Color(237, 224, 200);
	case 8:
		return sf::Color(242, 177, 121);
	case 16:
		return sf::Color(245, 149, 99);
	case 32:
		return sf::Color(246, 124, 95);
	case 64:
		return sf::Color(246, 94, 59);
	case 128:
		return sf::Color(237, 207, 114);
	case 256:
		return sf::Color(237, 204, 97);
	case 512:
		return sf::Color(237, 200, 80);
	case 1024:
		return sf::Color(237, 197, 63);
	case 2048:
		return sf::Color(237, 194, 46);
	default:
		return sf::Color(205, 193, 180);
	}
}

void createVector(std::vector<std::vector<int>>& board) {
	for (int i = 0; i < 4; i++) {
		std::vector<int> row;
		for (int j = 0; j < 4; j++) {
			row.push_back(8);
		}
		board.push_back(row);
	}
}

void drawRecTangle(sf::RenderWindow& window, float x, float y, sf::Color color, float sizeWidth, float sizeHight) {

	sf::RectangleShape newRectangle(sf::Vector2f(sizeWidth, sizeHight));

	newRectangle.setFillColor(color);
	newRectangle.setPosition(x, y);

	window.draw(newRectangle);

}
void drawText(sf::RenderWindow& window, sf::Font font, string text, int size, float x, float y, sf::Color color) {

	sf::Text newText;

	newText.setFont(font);
	newText.setString(text);
	newText.setCharacterSize(size);
	newText.setFillColor(color);
	newText.setPosition(x, y);

	window.draw(newText);

}
void drawPng(sf::RenderWindow& window, const string& path, float x, float y, float sizeX, float sizeY, sf::Color color) {
	sf::Texture newPng;
	sf::Sprite newSprite;
	if (!newPng.loadFromFile(path)) {
		cout << "Error loading file png " << path << endl;
		return;
	}
	newSprite.setTexture(newPng);
	newSprite.setScale(sizeX, sizeY);
	newSprite.setPosition(x, y);
	newSprite.setColor(color);
	window.draw(newSprite);
}

void drawDashBoard(sf::RenderWindow& window, sf::Font font) {
	drawText(window, font, "2048", 70, 100, 90, sf::Color(187, 173, 160));

	drawRecTangle(window, 280, 100, sf::Color(245, 149, 99), 100, 70);
	drawText(window, font, "Score", 25, 295, 110, sf::Color::White);

	drawRecTangle(window, 395, 100, sf::Color(245, 149, 99), 145, 70);
	drawText(window, font, "Best Score", 25, 405, 110, sf::Color::White);

	drawRecTangle(window, 425, 200, sf::Color(187, 173, 160), 40, 40);
	drawPng(window, "Undo.png", 421, 198, 0.2f, 0.2f, sf::Color::White);

	drawRecTangle(window, 475, 200, sf::Color(187, 173, 160), 40, 40);
	drawPng(window, "Redo.png", 471, 198, 0.2f, 0.2f, sf::Color::White);

	drawRecTangle(window, 145, 200, sf::Color(187, 173, 160), 40, 40);
	drawPng(window, "Refresh.jpg", 151, 206, 0.11f, 0.11f, sf::Color::White);

	drawRecTangle(window, 100, 200, sf::Color(187, 173, 160), 40, 40);
	drawPng(window, "Home.png", 100, 201, 0.4f, 0.4f, sf::Color::White);

}

void draw(std::vector<std::vector<int>> boardGame, sf::RenderWindow& window) {

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");



	drawDashBoard(window, font);




	//drawRecTangle(window, 200, 150, sf::Color(187, 173, 160), 0, 0);
	//drawPng(window, "Rectangle.png", float(243), float(85), 0.5f, 0.62f, sf::Color(245, 149, 99));



	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {


			sf::RectangleShape Shape(sf::Vector2f(static_cast<float>(95), static_cast<float>(95)));

			Shape.setPosition(static_cast<float>(j * 105 + 100), static_cast<float>(i * 105 + 265));
			Shape.setFillColor(getColor(boardGame[i][j]));
			Shape.setOutlineThickness(10);
			Shape.setOutlineColor(sf::Color(187, 173, 160));

			window.draw(Shape);

			if (boardGame[i][j] != 0) {
				sf::FloatRect TextRect;
				sf::Text text;
				sf::FloatRect textBounds = text.getLocalBounds();


				text.setFont(font);
				text.setString(to_string(boardGame[i][j]));
				text.setCharacterSize(40);
				text.setFillColor(sf::Color::Black);
				text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
				text.setPosition(static_cast<float>(j * 105 + 135), static_cast<float>(i * 105 + 285));


				window.draw(text);

			}
		}
	}
}

void CheckFps(sf::RenderWindow& window, sf::Clock& clock, double& starting) {
	double ending = clock.getElapsedTime().asSeconds();
	double timeFPS = ending - starting;
	string FPS;
	if (timeFPS > 0.0001) {
		FPS = to_string(int(1.0 / timeFPS));
	}
	window.setTitle("2048 FPS: " + FPS);
	starting = ending;

}


int main() {
	std::vector<std::vector<int>> boardGame;
	sf::RenderWindow window(sf::VideoMode(600, 800), "2048");
	sf::Clock clock;
	sf::Clock timeGame;
	sf::Text timeText;
	sf::Text timeText2;
	float timeLimitSeconds = 30.0f;
	float timeLimitMinutes = 1.0f;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");


	timeText.setFont(font);
	timeText.setCharacterSize(30);
	timeText.setFillColor(sf::Color::Black);
	timeText.setPosition(220, 200);

	timeText2.setFont(font);
	timeText2.setCharacterSize(30);
	timeText2.setFillColor(sf::Color::Black);
	timeText2.setPosition(200, 200);




	double starting = 0.0001;

	sf::View view(sf::FloatRect(0, 0, 600, 800));


	window.setFramerateLimit(60);
	createVector(boardGame);

	while (window.isOpen()) {
		sf::Event event;
		CheckFps(window, clock, starting);

		float escape = timeGame.getElapsedTime().asSeconds();
		float timePrint = timeLimitSeconds - escape;
		if (timePrint < 0 && timeLimitMinutes == 0) {
			timeText.setString("Time's up! You lost the game");
		}
		if (timePrint <= 0 && timeLimitMinutes > 0) {
			timeLimitMinutes--;
			timeLimitSeconds = 60.0f;
			timeGame.restart();
		}

		else {
			if (timeLimitMinutes < 10) {
				if (timePrint < 10) {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":0" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
				else {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
			}
			else {
				if (timePrint < 10) {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":0" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
				else {
					ostringstream temp;
					temp << "Time: 0" << static_cast<int>(timeLimitMinutes) << ":" << static_cast<int>(timePrint) << "s";
					timeText.setString(temp.str());
				}
			}
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				float Update_width = static_cast<float>(event.size.width);
				float Update_height = static_cast<float>(event.size.height);

				float Update_board = Update_width / Update_height;
				float board = 600.0f / 800.0f;

				if (Update_board > board) {
					view.setSize(static_cast <float>(800 * Update_board), static_cast <float>(800));
				}
				else {
					view.setSize(static_cast <float>(600), static_cast <float>(600 / Update_board));
				}
				window.setView(view);
			}
		}

		window.clear(sf::Color(245, 243, 227));

		draw(boardGame, window);
		window.draw(timeText);
		drawRecTangle(window, 10, 200, sf::Color::Black, 0, 0);

		window.display();
		//sf::sleep(sf::milliseconds(10));

	}

	return 0;
}
