#include <fstream>
#include "Menu.hh"
#include "Engine.hpp"

Menu::Menu()
{
	_spacing = 10;
	_fontsize = 14;
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
  if (!(xml = doc.load(ifs)) || !doc.child("menu"))
    {
      Engine::console->output(COLOR_ERROR, "Error: Menu: Invalid XML resource");
      return (false);
    }
  parseMenu(doc.child("menu"));
  int index = 0;
  for (pugi::xml_node item = doc.child("menu").child("item");
	  item != NULL;
	  item = item.next_sibling("item"), index++)
    {
      MenuItem *pItem;
      
	  if ((pItem = parseItem(item, index)) != NULL)
	  {
		  pItem->setFontsize(_fontsize);
		  _items.push_back(pItem);
	  }
    }
  return (true);
}

void Menu::parseMenu(pugi::xml_node &menu)
{
	if (menu.child("title"))
		_title.setString(menu.child_value("title"));
	if (menu.child("spacing"))
		_spacing = atoi(menu.child_value("spacing"));
	if (menu.child("fontsize"))
		_fontsize = atoi(menu.child_value("fontsize"));
}

MenuItem *Menu::parseItem(pugi::xml_node &item, int &index)
{
  MenuItem *pItem;
  MenuItemType type;

  type = MenuItem::typeMap[item.attribute("type").value()];
  pItem = MenuItem::factory(type);
  pItem->setLabel(item.child_value("label"));
  if (type == Setting)
    {
      std::vector<std::string> values;
	  
	  if (item.child("padding"))
		  static_cast<MenuSetting *>(pItem)->setPadding(atoi(item.child_value("padding")));
      for (pugi::xml_node setting = item.child("setting");
	   setting != NULL;
	   setting = setting.next_sibling("item"))
		{
			values.push_back(setting.text().as_string());
		}
      (static_cast<MenuSetting *>(pItem))->setValues(values);
    }
  if (item.child("color"))
	  pItem->setColor(Console::convertColorCode(item.child_value("color"), "#"));
  else
	  pItem->setColor(sf::Color::White);
  if (item.child("x"))
	  pItem->setXOffset(atoi(item.child_value("x")));
  else
	  pItem->setXOffset(50);
  if (item.child("y"))
	  pItem->setXOffset(atoi(item.child_value("y")));
  else
	  pItem->setYOffset(_spacing + (index * _spacing));
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
