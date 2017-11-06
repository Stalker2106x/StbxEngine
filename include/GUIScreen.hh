/*!
* @file      GUIScreen.hh
* @class     stb::GUIScreen
* @brief     Representation of out-of-game interfaces with various elements.
*
*            This class provides a container to arrange multiple GUIElements together with Menus
*
*/
#ifndef GUISCREEN_HH_
#define GUISCREEN_HH_


#ifdef STBXENGINE_CORE
#include <pugixml.hpp>
#endif
#include "GUIXML.hh"

namespace stb {

	class GUIScreen : public GUIPanel
	{
	public:
		GUIScreen(GUIElement *parent);
		~GUIScreen();

		static GUIScreen *loadFromFile(const std::string &file, const std::string &screenId = "");

	};

}

#endif /* !GUISCREEN_HH_ */