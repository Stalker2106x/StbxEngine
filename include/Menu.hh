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
#include "MenuItem.hh"

typedef std::vector<MenuItem *> itemTab;

class Menu
{
public:
  Menu();
  ~Menu();

  bool loadFromFile(const std::string &file);
  MenuItem *parseItem(pugi::xml_node &item);
  
  bool update(sf::Event &e);
  void draw(sf::RenderWindow *);

protected:
  int _id, _parentId;
  sf::Text _title;
  itemTab _items;
};

#endif /* MENU_HH_ */
