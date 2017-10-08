/*!
 * @file      Menu.hh
 * @class     Menu
 * @brief     Simple class for generating menus.
 *
 *            This class is used to build menus from XML, and handle user behaviour inside.
 */

#ifndef MENU_HH_
#define MENU_HH_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "MenuItem.hh"

#ifdef STBXENGINE_CORE
#include <pugixml.hpp>
#endif

namespace stb {

	typedef void(*menuFptr)(void *);
	typedef std::vector<MenuItem *> itemTab;

	class Menu
	{
	public:
		Menu();
		~Menu();

		void reset();
		bool loadFromFile(const std::string &file);
#ifdef STBXENGINE_CORE
		void parseMenu(pugi::xml_node menu);
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

		void setBackground(const std::string &resource);

		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *);

		static std::unordered_map<std::string, std::pair<menuFptr, void *>> customAction;
		static std::unordered_map<std::string, std::vector<std::string>> dynamicValue;
	protected:
		int _id, _parentId;
		int _spacing, _fontsize;
		sf::Sprite _background;
		sf::Text _title;
		itemTab _items;
	};

}

#endif /* MENU_HH_ */
