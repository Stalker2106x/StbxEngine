/*!
 * @file      GUIMenu.hh
 * @class     GUIMenu
 * @brief     Simple class for generating GUI menus.
 *
 *            This class is used to build menus from XML, and handle user behaviour inside.
 */

#ifndef GUIMENU_HH_
#define GUIMENU_HH_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GUIMenuItem.hh"

#ifdef STBXENGINE_CORE
#include <pugixml.hpp>
#endif

namespace stb {

	class GUIScreen; //Forward

	typedef void(*menuFptr)(void *);
	typedef std::vector<MenuItem *> itemTab;

	class Menu : public GUIElement
	{
	public:
		Menu(GUIScreen *screenHandle);
		~Menu();

		void reset();
#ifdef STBXENGINE_CORE
		static Menu *parseXML(GUIScreen *screenHandle, pugi::xml_node &menu);
		void parseMenu(const pugi::xml_node &menu);
		MenuItem *parseItem(pugi::xml_node &item, size_t &index);
		void parseGeneric(pugi::xml_node &item, MenuItem *pItem, size_t & index);
		void parseLink(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
		void parseSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
		void parseDynamicSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
		void parseEdit(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
		void parseSlider(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
		void parseCheckbox(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
#endif
		void initializeItems();

		virtual void setPosition(const sf::Vector2f &pos);
		void setBackground(const std::string &resource);

		void Menu::changeScreen(const std::string &file);

		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *);

		static std::unordered_map<std::string, std::pair<menuFptr, void *>> customAction;
		static std::unordered_map<std::string, std::vector<std::string>> dynamicValue;
	protected:
		GUIScreen *_screenHandle;
		int _id, _parentId;
		int _spacing, _fontsize;
		sf::Sprite _background;
		sf::Text _title;
		itemTab _items;
	};

}

#endif /* !GUIMENU_HH_ */
