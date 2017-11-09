#include "utils.h"

namespace stb {

	GUIResourceDefaults GUIDefaults;

	const sf::Color convertColorCode(std::string code, std::string esc)
	{
		sf::Color color;

		if (code.length() < (9 + esc.length()))
			return (sf::Color::White);
		if (code.find(esc) == 0)
			code = code.substr(esc.length(), 9);
		color.r = atoi(code.substr(0, 3).c_str());
		color.g = atoi(code.substr(3, 3).c_str());
		color.b = atoi(code.substr(6, 3).c_str());
		if (code.length() >= (12 + esc.length()))
			color.a = atoi(code.substr(9, 3).c_str());
		else
			color.a = 255;
		return (color);
	}

}