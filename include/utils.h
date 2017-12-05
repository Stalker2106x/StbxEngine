/*!
* @file      utils.hh
* @brief     None
*
*            N/A
*/
#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "defs.h"

namespace stb {

	const sf::Color convertColorCode(std::string code, std::string esc = COLOR_ESC);
#ifdef PUGIXML_WCHAR_MODE
	const std::wstring getIconCode(const std::string &id);
#endif
	const Direction convertDirection(const std::string &direction);
}

#endif /* UTILS_H_ */