#include <fstream>
#include "GUIMenu.hh"
#include "Resolver.hh"
#include "Engine.hpp"
#include "GUIScreen.hh"

using namespace stb;

std::unordered_map<std::string, std::pair<menuFptr, void *>> stb::GUIMenu::customAction = std::unordered_map<std::string, std::pair<menuFptr, void *>>();
std::unordered_map<std::string, std::vector<std::string>> stb::GUIMenu::dynamicValue = std::unordered_map<std::string, std::vector<std::string>>();

GUIMenu::GUIMenu(GUIScreen *screenHandle)
{
	_screenHandle = screenHandle;
	_spacing = 10;
	_fontsize = 20;
}

GUIMenu::~GUIMenu()
{

}

void GUIMenu::reset()
{
	_items.clear();
}

GUIMenu *GUIMenu::parseXML(GUIScreen *screenHandle, pugi::xml_node &menu)
{
	GUIMenu *pMenu = new GUIMenu(screenHandle);
	pMenu->parseMenu(menu);
	size_t index = 0;
	for (pugi::xml_node item = menu.child("item");
		item != NULL;
		item = item.next_sibling("item"), index++)
	{
		GUIMenuItem *pItem;
      
		if ((pItem = pMenu->parseItem(item, index)) != NULL)
		{
			pItem->setFontsize(pMenu->_fontsize);
			pMenu->_items.push_back(pItem);
		}
	}
	pMenu->initializeItems();
	return (pMenu);
}

void GUIMenu::parseMenu(const pugi::xml_node &menu)
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

GUIMenuItem *GUIMenu::parseItem(pugi::xml_node &item, size_t &index)
{
  GUIMenuItem *pItem;
  GUIMenuItemType type;

  try { type = GUIMenuItem::typeMap.at(item.attribute("type").value()); }
  catch (...) { return (NULL); }
  pItem = GUIMenuItem::factory(type);
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
  parseGeneric(item, pItem, index);
  return (pItem);
}

void GUIMenu::parseGeneric(pugi::xml_node &item, GUIMenuItem *pItem, size_t &index)
{
	pItem->setLabel(item.child_value("label"));
	if (item.child("color"))
		pItem->setColor(*Console::convertColorCode(item.child_value("color"), "#"));
	else
		pItem->setColor(sf::Color::White); //set default white
	if (item.child("padding"))
		pItem->setPadding(atoi(item.child_value("padding")));
	if (item.attribute("x"))
	{
		index--;
		pItem->setXOffset(atof(item.attribute("x").value()));
	}
	else
	{
		pItem->setXOffset(50);
		//pItem->setXOffset((Engine::instance->getWindowSize().x - pItem->getPadding()) - 100);
	}
	if (item.attribute("y"))
	{
		index--;
		pItem->setXOffset(atof(item.attribute("y").value()));
	}
	else
		pItem->setYOffset(_spacing + (static_cast<float>(index)* _spacing));
}

void GUIMenu::parseLink(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuLink *sItem = dynamic_cast<GUIMenuLink *>(pItem);

	sItem->setMenuHandle(this); //Adding Handle for moving
	if (item.attribute("target"))
		sItem->setTarget(item.attribute("target").value());
	if (item.attribute("action"))
	{
		std::string action = item.attribute("action").value();
		sItem->setCustomAction(GUIMenu::customAction[action].first, GUIMenu::customAction[action].second);
	}
	if (item.attribute("command"))
	{
		sItem->setCommand(item.attribute("command").value());
	}
}

void GUIMenu::parseSetting(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuSetting *sItem = dynamic_cast<GUIMenuSetting *>(pItem);
	std::vector<std::string> values;

	for (pugi::xml_node setting = item.child("setting");
		setting != NULL;
		setting = setting.next_sibling("setting"))
	{
		values.push_back(setting.text().as_string());
	}
	sItem->setValues(values);
}

void GUIMenu::parseDynamicSetting(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuDynamicSetting *sItem = dynamic_cast<GUIMenuDynamicSetting *>(pItem);

	if (item.attribute("filler"))
		sItem->setValues(dynamicValue[item.attribute("filler").value()]);
}

void GUIMenu::parseEdit(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuEdit *sItem = dynamic_cast<GUIMenuEdit *>(pItem);
	sf::Color *inputColor = NULL;
	sf::Color *valueColor = NULL;

	if (item.child("inputlength"))
		sItem->setInputLength(atof(item.child_value("inputlength")));
	if (item.child("inputcolor"))
		inputColor = Console::convertColorCode(item.child_value("inputcolor"), "#");
	sItem->setInputColor(inputColor, valueColor);
}

void GUIMenu::parseSlider(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuSlider *sItem = dynamic_cast<GUIMenuSlider *>(pItem);
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

void GUIMenu::parseCheckbox(pugi::xml_node &item, GUIMenuItem *pItem, const size_t &/* index */)
{
	GUIMenuCheckbox *sItem = dynamic_cast<GUIMenuCheckbox *>(pItem);
	sf::Color *containerColor = NULL;
	sf::Color *fillColor = NULL;

	if (item.child("bcolor"))
		containerColor = Console::convertColorCode(item.child_value("bcolor"), "#");
	if (item.child("fcolor"))
		fillColor = Console::convertColorCode(item.child_value("fcolor"), "#");
	sItem->setCheckboxColor(containerColor, fillColor);
}

void GUIMenu::initializeItems()
{
	std::vector<GUIMenuItem *>::iterator it = _items.begin();
	while (it != _items.end())
	{
		(*it)->initialUpdate();
		it++;
	}
}

void GUIMenu::setBackground(const std::string &resource)
{
	_background.setTexture(*Resolver<sf::Texture>::resolve(resource));
}

void GUIMenu::setPosition(const sf::Vector2f &pos)
{
	for (size_t i = 0; i < _items.size(); i++) //EXPERIMENTAL
	{
		_items[i]->setXOffset(pos.x);
		_items[i]->setYOffset(pos.y);
	}
}

void GUIMenu::changeScreen(const std::string &file)
{
	_screenHandle->changeScreen(file);
}

bool GUIMenu::update(const sf::Event &e)
{
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->update(e);
  return (true);
}

void GUIMenu::draw(sf::RenderWindow *win)
{
  win->draw(_background);
  win->draw(_title);
  for (size_t i = 0; i < _items.size(); i++)
    _items[i]->draw(win);
}
