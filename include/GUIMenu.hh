/*!
 * @file      GUIMenu.hh
 * @class     stb::GUIMenu
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
	typedef std::vector<GUIMenuItem *> itemTab;

	class GUIMenu : public GUIElement
	{
	public:
		GUIMenu();
		~GUIMenu();

		virtual void initialUpdate();

#ifdef STBXENGINE_CORE
		static GUIMenu *parseXML(const pugi::xml_node &menu);
		void parseMenu(const pugi::xml_node &menu);
		GUIMenuItem *parseItem(pugi::xml_node &item, size_t &index);
		void parseGeneric(pugi::xml_node &item, GUIMenuItem *pItem, size_t & index);
		void parseLink(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
		void parseSetting(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
		void parseDynamicSetting(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
		void parseEdit(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
		void parseSlider(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
		void parseCheckbox(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &index);
#endif
		void initializeItems();

		virtual void setPosition(const sf::Vector2f &pos);

		virtual const sf::Vector2f &getPosition();
		virtual const sf::Vector2f getSize() { return (sf::Vector2f(0, 0)); };
		
		bool update(const sf::Event &e);
		void draw(sf::RenderWindow *);

		static std::unordered_map<std::string, std::pair<menuFptr, void *>> customAction;
		static std::unordered_map<std::string, std::vector<std::string>> dynamicValue;

	protected:
		int _id, _parentId;
		int _spacing, _fontsize;
		itemTab _items;
	};

}

#endif /* !GUIMENU_HH_ */
