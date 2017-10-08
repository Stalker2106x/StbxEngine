#include <fstream>
#include "Menu.hh"
#include "Resolver.hh"
#include "Engine.hpp"

using namespace stb;

std::unordered_map<std::string, std::pair<menuFptr, void *>> stb::Menu::customAction = std::unordered_map<std::string, std::pair<menuFptr, void *>>();
std::unordered_map<std::string, std::vector<std::string>> stb::Menu::dynamicValue = std::unordered_map<std::string, std::vector<std::string>>();

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
      Engine::instance->console->output(COLOR_ERROR, "Error: Menu: XML resource not found");
      return (false);
    }
  if (!(xml = doc.load(ifs)) || !doc.child("menu"))
    {
	  Engine::instance->console->output(COLOR_ERROR, "Error: Menu: Invalid XML resource");
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
		  _items.push_back(pItem);
	  }
    }
  initializeItems();
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

MenuItem *Menu::parseItem(pugi::xml_node &item, size_t &index)
{
  MenuItem *pItem;
  MenuItemType type;

  try { type = MenuItem::typeMap.at(item.attribute("type").value()); }
  catch (...) { return (NULL); }
  pItem = MenuItem::factory(type);
  parseGeneric(item, pItem, index);
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
  else if (type == Checkbox)
	  parseCheckbox(item, pItem, index);
  return (pItem);
}

void Menu::parseGeneric(pugi::xml_node &item, MenuItem *pItem, size_t &index)
{
	pItem->setLabel(item.child_value("label"));
	if (item.child("color"))
		pItem->setColor(*Console::convertColorCode(item.child_value("color"), "#"));
	else
		pItem->setColor(sf::Color::White); //set default white
	if (item.child("padding"))
		pItem->setPadding(atoi(item.child_value("padding")));
	if (item.child("x"))
	{
		index--;
		pItem->setXOffset(atof(item.child_value("x")));
	}
	else
	{
		pItem->setXOffset(50);
		//pItem->setXOffset((Engine::instance->getWindowSize().x - pItem->getPadding()) - 100);
	}
	if (item.child("y"))
	{
		index--;
		pItem->setXOffset(atof(item.child_value("y")));
	}
	else
		pItem->setYOffset(_spacing + (static_cast<float>(index)* _spacing));
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
	sItem->setInputColor(inputColor, valueColor);
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

void Menu::parseCheckbox(pugi::xml_node &item, MenuItem *pItem, const size_t &/* index */)
{
	MenuCheckbox *sItem = dynamic_cast<MenuCheckbox *>(pItem);
	sf::Color *containerColor = NULL;
	sf::Color *fillColor = NULL;

	if (item.child("bcolor"))
		containerColor = Console::convertColorCode(item.child_value("bcolor"), "#");
	if (item.child("fcolor"))
		fillColor = Console::convertColorCode(item.child_value("fcolor"), "#");
	sItem->setCheckboxColor(containerColor, fillColor);
}

void Menu::initializeItems()
{
	std::vector<MenuItem *>::iterator it = _items.begin();
	while (it != _items.end())
	{
		(*it)->initialUpdate();
		it++;
	}
}

void Menu::setBackground(const std::string &resource)
{
	_background.setTexture(*Resolver<sf::Texture>::resolve(resource));
}

bool Menu::update(const sf::Event &e)
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
