/*!
* @file      defs.hh
* @brief     None
*
*            Standard STBX Defines
*/
#ifndef DEFS_H_
#define DEFS_H_

#include <sstream>
#include <SFML/Graphics.hpp>

namespace stb {

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

	struct GUIResourceDefaults
	{
		int fontSize;
		std::string font;
		std::string fontColor;
		int panelSpacing;
		int pairSpacing;
		int gridSpacing;
	};
	extern GUIResourceDefaults GUIDefaults;

}

#endif /* DEFS_H_ */