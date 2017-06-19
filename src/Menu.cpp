#include <fstream>
#include <pugixml/src/pugixml.hpp>
#include "Menu.hh"
#include "Engine.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{

}

bool Menu::loadFromFile(std::string &file)
{
  pugi::xml_document doc;
  std::ifstream ifs(file);
  pugi::xml_parse_result xml;

  if (!(xml = doc.load(ifs)))
    Engine::console->output(COLOR_ERROR, "Error: Menu: Invalid XML resource");
  _title = doc.child("menu").child("title").child_value();
  for (pugi::xml_node item = doc.child("item"); item != NULL; item = item.next_sibling("item"))
    {
      MenuItemType type = MenuItem::typeMap[item.attribute("type").value()];
      _items.push_back(MenuItem::factory(type));
      _items.back()->setLabel(item.child("title").value());
      if (type == Setting)
	{
	  std::vector<std::string> values;
	  
	  for (pugi::xml_node setting = item.child("setting");
	       setting != NULL; setting = setting.next_sibling("item"))
	    {
	      values.push_back(setting.value());
	    }
	}
    }
  return (true);
}

/*void Menu::bindActions(std::vector<action> &actions)
{
  for (size_t i = 0; i < _items.size(); i++)
    if (actions[i] != NULL)
      _items[i].second = actions[i];
      }*/

bool Menu::update(sf::Event &e)
{
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->update(e);
  return (true);
}

void Menu::draw(sf::RenderWindow *win)
{
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->draw(win);
}
