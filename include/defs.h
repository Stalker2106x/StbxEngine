/*!
* @file      defs.hh
* @brief     None
*
*            Standard Definitions
*/
#ifndef DEFS_H_
#define DEFS_H_

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

}

#endif /* DEFS_H_ */