#include <fstream>
#include "Menu.hh"
#include "Resolver.hh"
#include "Engine.hpp"

std::unordered_map<std::string, std::pair<menuFptr, void *>> Menu::customAction = std::unordered_map<std::string, std::pair<menuFptr, void *>>();
std::unordered_map<std::string, std::vector<std::string>> Menu::dynamicValue = std::unordered_map<std::string, std::vector<std::string>>();

Menu::Menu()
{
	_spacing = 10;
	_fontsize = 20;
}

Menu::~Menu()
{

}

void Menu::reset()
{
	_items.clear();
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
  size_t index = 0;
  for (pugi::xml_node item = doc.child("menu").child("item");
	  item != NULL;
	  item = item.next_sibling("item"), index++)
    {
      MenuItem *pItem;
      
	  if ((pItem = parseItem(item, index)) != NULL)
	  {
		  pItem->setFontsize(_fontsize);
		  pItem->initialUpdate();
		  _items.push_back(pItem);
	  }
    }
  return (true);
}

void Menu::parseMenu(pugi::xml_node menu)
{
	if (menu.child("title"))
		_title.setString(menu.child_value("title"));
	if (menu.child("background"))
		setBackground(menu.child_value("background"));
	if (menu.child("spacing"))
		_spacing = atoi(menu.child_value("spacing"));
	if (menu.child("fontsize"))
		_fontsize = atoi(menu.child_value("fontsize"));
}

MenuItem *Menu::parseItem(pugi::xml_node &item, const size_t &index)
{
  MenuItem *pItem;
  MenuItemType type;

  try { type = MenuItem::typeMap.at(item.attribute("type").value()); }
  catch (...) { return (NULL); }
  pItem = MenuItem::factory(type);
  pItem->setLabel(item.child_value("label"));
  if (type == Link)
	  parseLink(item, pItem, index);
  else if (type == Setting)
	  parseSetting(item, pItem, index);
  else if (type == DynamicSetting)
	  parseDynamicSetting(item, pItem, index);
  else if (type == Edit)
	  parseEdit(item, pItem, index);
  else if (type == Slider)
	  parseSlider(item, pItem, index);
  if (item.child("color"))
	  pItem->setColor(*Console::convertColorCode(item.child_value("color"), "#"));
  else
	  pItem->setColor(sf::Color::White);
  if (item.child("padding"))
	  pItem->setPadding(atoi(item.child_value("padding")));
  if (item.child("x"))
	  pItem->setXOffset(atof(item.child_value("x")));
  else
	  pItem->setXOffset(50);
  if (item.child("y"))
	  pItem->setXOffset(atof(item.child_value("y")));
  else
	  pItem->setYOffset(_spacing + (index * _spacing));
  return (pItem);
}

void Menu::parseLink(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuLink *sItem = dynamic_cast<MenuLink *>(pItem);

	sItem->setMenuHandle(this); //Adding Handle for moving
	if (item.attribute("target"))
		sItem->setTarget(item.attribute("target").value());
	if (item.attribute("action"))
	{
		std::string action = item.attribute("action").value();
		sItem->setCustomAction(Menu::customAction[action].first, Menu::customAction[action].second);
	}
	if (item.attribute("command"))
	{
		sItem->setCommand(item.attribute("command").value());
	}
}

void Menu::parseSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuSetting *sItem = dynamic_cast<MenuSetting *>(pItem);
	std::vector<std::string> values;

	for (pugi::xml_node setting = item.child("setting");
		setting != NULL;
		setting = setting.next_sibling("setting"))
	{
		values.push_back(setting.text().as_string());
	}
	sItem->setValues(values);
}

void Menu::parseDynamicSetting(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuDynamicSetting *sItem = dynamic_cast<MenuDynamicSetting *>(pItem);

	if (item.attribute("filler"))
		sItem->setValues(dynamicValue[item.attribute("filler").value()]);
}

void Menu::parseEdit(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuEdit *sItem = dynamic_cast<MenuEdit *>(pItem);
	sf::Color *inputColor = NULL;
	sf::Color *valueColor = NULL;

	if (item.child("inputlength"))
		sItem->setInputLength(atof(item.child_value("inputlength")));
	if (item.child("inputcolor"))
		inputColor = Console::convertColorCode(item.child_value("inputcolor"), "#");
	sItem->setColor(inputColor, valueColor);
}

void Menu::parseSlider(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuSlider *sItem = dynamic_cast<MenuSlider *>(pItem);
	sf::Color *barColor = NULL;
	sf::Color *fillColor = NULL;

	if (item.child("bcolor"))
		barColor = Console::convertColorCode(item.child_value("bcolor"), "#");
	if (item.child("fcolor"))
		fillColor = Console::convertColorCode(item.child_value("fcolor"), "#");
	sItem->setBarColor(barColor, fillColor);
	if (item.child("barwidth"))
		sItem->setBarWidth(atoi(item.child_value("barwidth")));
}

void Menu::setBackground(const std::string &resource)
{
	_background.setTexture(*Resolver<sf::Texture>::resolve("background"));
}

bool Menu::update(sf::Event &e)
{
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->update(e);
  return (true);
}

void Menu::draw(sf::RenderWindow *win)
{
  win->draw(_background);
  win->draw(_title);
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->draw(win);
}
