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
  pugi::xml_document doc;
  std::ifstream ifs(file);
  pugi::xml_parse_result xml;

  if (!(xml = doc.load(ifs)))
    {
      //ERROR ON FILE SYNTAX
    }
  _title = doc.child("menu").child("title").child_value();
  pugi::xml_node items = doc.child("item");
  //Parse xml
  std::cout << _title;
  return (true);
}

void Menu::bindActions(actionTab actions)
{
  for (size_t i = 0; i < _items.size(); i++)
    if (actions[i] != NULL)
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
