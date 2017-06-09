#ifndef MENUITEM_HH_
#define MENUITEM_HH_

#include <SFML/Graphics.hpp>

class MenuItem
{
public:
  MenuItem(std::string &);
  ~MenuItem();

  void setPosition(sf::Vector2f &pos);

  virtual void onClick(void *) = 0;
  
protected:
  sf::Text _label;
};

class MenuLink : public MenuItem
{

};

class MenuEdit : public MenuItem
{

};

class MenuStaticSetting : public MenuItem
{

};

class MenuDynamicSetting : public MenuItem
{

};

class MenuSliderSetting : public MenuItem
{

};

#endif
