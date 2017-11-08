/*!
* @file      GUI.hh
* @class     stb::GUI
* @brief     Heads up display module
*
*            This classes set provide usable GUI to draw info over the renderer frame.
*            It acts as a container for GUI Elements like static or dynamic Panels and Indicators to be added anywhere on screen.
*/
#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>
#include <SFML/Graphics.hpp>
#include "GUIElement.hpp"

namespace stb {

#define DEFAULT_ID	""
#define COLOR_ESC	("\\\\#")

	enum Orientation {
		Horizontal,
		Vertical
	};

	enum Direction {
		Left,
		Up,
		Right,
		Down
	};

	const sf::Color convertColorCode(std::string code, std::string esc = COLOR_ESC);
	
	template <typename T>
	T convertSize(std::string size, Orientation o, GUIElement *parent)
	{
		std::istringstream iss;
		T computed = 0;
		size_t pos;

		if ((pos = size.find("%")) != std::string::npos)
		{
			iss.str(size.substr(0, size.length() - (pos - 1)));
			iss >> computed;
			if (parent == NULL)
				computed = (o == Horizontal ? Engine::instance->getWindowSize().x : Engine::instance->getWindowSize().y) * (computed / 100.0f); //No parent, use window as parent
			else
				computed = (o == Horizontal ? parent->getSize().x : parent->getSize().y) * (computed / 100.0f);
		}
		else
		{
			if ((pos = size.find("px")) != std::string::npos)
			{
				size = size.substr(0, size.length() - (pos - 1));
			}
			iss.str(size);
			iss >> computed;
		}
		return (computed);
	}

}

#endif /* UTILS_H_ */