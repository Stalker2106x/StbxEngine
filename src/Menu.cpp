#include <fstream>
#include "Menu.hh"
#include "Engine.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{

}

bool Menu::loadFromFile(const std::string &file)
{
  pugi::xml_document doc;
  std::ifstream ifs(file);
  pugi::xml_parse_result xml;

  if (!ifs)
    {
      Engine::console->output(COLOR_ERROR, "Error: Menu: XML resource not found");
      return (false);
    }
  if (!(xml = doc.load(ifs)))
    {
      Engine::console->output(COLOR_ERROR, "Error: Menu: Invalid XML resource");
      return (false);
    }
  _title.setString(doc.child("menu").child("title").child_value());
  int index = 0;
  for (pugi::xml_node item = doc.child("menu").child("item");
	  item != NULL;
	  item = item.next_sibling("item"), index++)
    {
      MenuItem *pItem;
      
      if ((pItem = parseItem(item, index)) != NULL)
	  _items.push_back(pItem);
    }
  return (true);
}

MenuItem *Menu::parseItem(pugi::xml_node &item, int &index)
{
  MenuItem *pItem;
  MenuItemType type;

  type = MenuItem::typeMap[item.attribute("type").value()];
  pItem = MenuItem::factory(type);
  pItem->setLabel(item.child_value("label"));
  if (item.child("color"))
	  pItem->setColor(Console::convertColorCode(item.child_value("color"), "#"));
  else
	  pItem->setColor(sf::Color::White);
  if (item.child("pos"))
	  pItem->setPosition(sf::Vector2f(10, 50 + (index * 50))); //NEEDS REFACTOR
  else
    pItem->setPosition(sf::Vector2f(10, 50 + (index * 50)));
  if (type == Setting)
    {
      std::vector<std::string> values;
	  
      for (pugi::xml_node setting = item.child("setting");
	   setting != NULL;
	   setting = setting.next_sibling("item"))
	{
	  values.push_back(setting.value());
	}
      (static_cast<MenuSetting *>(pItem))->setValues(values);
    }
  return (pItem);
}

bool Menu::update(sf::Event &e)
{
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->update(e);
  return (true);
}

void Menu::draw(sf::RenderWindow *win)
{
  win->draw(_title);
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->draw(win);
}
