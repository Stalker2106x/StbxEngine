#ifndef MENU_HH_
#define MENU_HH_

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <pugixml/src/pugixml.hpp>

typedef void (*action)(int);
typedef std::vector<action> actionTab;
typedef std::vector<std::pair<sf::Text, action>> itemTab;

class Menu
{
public:
  Menu();
  ~Menu();

  bool loadFromFile(std::string &file);
  void bindActions(actionTab actions);

  bool update(sf::Event &e);
  void draw(sf::RenderWindow *);

protected:
  int _id, _parentId;
  std::string _title;
  itemTab _items;

  int _hover;
};

#endif /* MENU_HH_ */
