#pragma once

#include <SFML/Graphics.hpp>
#include "ColorGame.h"


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