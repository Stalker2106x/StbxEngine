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
#include <pugixml/src/pugixml.hpp>
#include "MenuItem.hh"

typedef void(*menuFptr)(void *);
typedef std::vector<MenuItem *> itemTab;

class Menu
{
public:
  Menu();
  ~Menu();

  bool loadFromFile(const std::string &file);
  void parseMenu(pugi::xml_node menu);
  MenuItem *parseItem(pugi::xml_node &item, const size_t &index);
  void parseLink(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
  void parseSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
  void parseDynamicSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
  void parseEdit(pugi::xml_node &item, MenuItem *pItem, const size_t &index);
  void parseSlider(pugi::xml_node &item, MenuItem *pItem, const size_t &index);

  bool update(sf::Event &e);
  void draw(sf::RenderWindow *);

  static std::unordered_map<std::string, std::pair<menuFptr, void *>> customAction;
  static std::unordered_map<std::string, std::vector<std::string>> dynamicValue;
protected:	
  int _id, _parentId;
  int _spacing, _fontsize;
  sf::Text _title;
  itemTab _items;
};

#endif /* MENU_HH_ */
