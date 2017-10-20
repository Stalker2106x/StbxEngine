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
#include "GUIMenu.hh"

namespace stb {

	class GUIScreen : public GUIPanel
	{
	public:
		GUIScreen();
		~GUIScreen();

		bool loadFromFile(const std::string &file, const std::string &screenId = "");

#ifdef STBXENGINE_CORE
		void parseScreen(const pugi::xml_node &screen);
		bool isScreenParam(const pugi::xml_node &param);
#endif
	};

}

#endif /* !GUISCREEN_HH_ */