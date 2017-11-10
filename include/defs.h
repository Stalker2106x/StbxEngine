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

namespace stb {

	//Standard STBX Defines
#define DEFAULT_ID	L""
#define COLOR_ESC	("\\\\#")
#define COLOR_ERROR	("\\\\#240077077")
#define COLOR_SUCCESS	("\\\\#154205050")
#define COLOR_INFO	("\\\\#000191255")

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