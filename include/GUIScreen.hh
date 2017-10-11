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

#include "GUIMenu.hh"

namespace stb {

	class GUIScreen : public GUIElement
	{
	public:
		GUIScreen();
		~GUIScreen();

		virtual void setPosition(const sf::Vector2f &pos);
		virtual const sf::Vector2f &getPosition();

		void reset();

		bool loadFromFile(const std::string &file, const std::string &screenId = "");

#ifdef STBXENGINE_CORE
		void parseScreen(const pugi::xml_node &screen);
#endif

		void changeScreen(const std::string &id, const std::string &location);

		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *win);

	private:
		std::string _lastLocation, _changeLocation, _changeId;
		GUIPanel _container;
		GUIMenu *_menu;
	};

}

#endif /* !GUISCREEN_HH_ */