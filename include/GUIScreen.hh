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

		void reset();

		bool loadFromFile(const std::string &file);

		void changeScreen(const std::string &location);

		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *win);

	private:
		std::string _changeLocation;
		GUIPanel _container;
		GUIMenu *_menu;
	};

}

#endif /* !GUISCREEN_HH_ */