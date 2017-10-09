/*!
* @file      GUIScreen.hh
* @class     GUIScreen
* @brief     Representation of out-of-game interfaces with various elements.
*
*            This class provides a container to arrange multiple GUIElements together with Menus
*
*/

#ifndef GUISCREEN_HH_
#define GUISCREEN_HH_

#include "GUIMenu.hh"

namespace stb {

	class GUIScreen
	{
	public:
		GUIScreen();
		~GUIScreen();

	private:

		GUIPanel _container;
		Menu *_menu;
	};

}

#endif /* !GUISCREEN_HH_ */