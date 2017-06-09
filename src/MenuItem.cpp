#include "MenuItem.hh"

MenuItem::MenuItem(std::string &str)
{
  _label.setString(str);
}

MenuItem::~MenuItem()
{

}

void MenuItem::setPosition(sf::Vector2f &pos)
{
  _label.setPosition(pos.x, pos.y);
}
