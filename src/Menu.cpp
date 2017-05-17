#include "Menu.hh"

Menu::Menu()
{
  _hover = 0;
}

Menu::~Menu()
{

}

bool Menu::loadFromFile(std::string &file)
{
  tinyxml2::XMLDocument xml;

  xml.LoadFile(file.c_str());
  return (true);
}

void Menu::bindActions(actionTab actions)
{
  for (size_t i = 0; i < actions.size(); i++)
    _items[i].second = actions[i];
}

bool Menu::update(sf::Event &e)
{
  return (true);
}

void Menu::draw(sf::RenderWindow *win)
{
  for (size_t i = 0; i < _items.size(); i++)
    win->draw(_items[i].first);
}
