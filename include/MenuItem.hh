/*!
 * @file      MenuItem.hh
 * @brief     Menu items (links, settings, sliders, text inputs, ...)
 *
 *            This classes set provide usables objects for all kinds of items in a menu.
 *            It defines Links, Settings, and Edit types,which are specialized in child objects
 *            like Sliders, Static and Dynamic enums for Settings, and Key or String for Edit.
 */

#ifndef MENUITEM_HH_
#define MENUITEM_HH_

#include <SFML/Graphics.hpp>

enum MenuItemType {
  Link,
  Setting,
  DynamicSetting,
  Edit,
  Slider
};

/*!
 * @class MenuItem
 * @brief Abstract Menu item
 *
 *        This class is not instanciable. It is used as an abstract layer to store Items generically in Menu class.
 */
class MenuItem
{
public:
  MenuItem();
  ~MenuItem();

  static MenuItem *factory(const MenuItemType &type);
  
  bool isHovered() const;

  void setLabel(const std::string &label);
  virtual void setColor(const sf::Color &color);
  void setCustomAction(void (*fptr)(void));
  void setPosition(const sf::Vector2f &pos);

  virtual void onHover(bool triggered);
  virtual void onClick() = 0;

  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);

  static std::map<std::string, MenuItemType> typeMap;
  
protected:
  void (*_customPtr)(void);
  sf::Text _label;
  bool _hover;
};

/*!
 * @class MenuLink
 * @brief Menu link to another menu or action
 *
 *        Link defines a MenuItem that is clickable and points towards another menu or do a specific action (quit, apply settings, ...)
 */
class MenuLink : public MenuItem
{
public:
  MenuLink();
  ~MenuLink();

  void onClick();
};

/*!
 * @class MenuSetting
 * @brief Static Setting item, showing a list of values defined in XML.
 *
 *        This class holds a static enum defined in XML, for dynamic values, use child MenuDynamicSetting
 */
class MenuSetting : public MenuItem
{
public:
  MenuSetting();
  ~MenuSetting();

  void onClick();
  void onRClick();

  void setValues(std::vector<std::string> &values, const int &defaultIndex = 0);
  
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);

private:
  sf::Text _value;
  std::vector<std::string> _values;
  int _index;
};

/*!
 * @class MenuDynamicSetting
 * @brief Dynamic Setting item, showing a list of values known only at runtime.
 *
 *        This class holds a dynamic enum filled at runtime, for static values, use parent MenuSetting
 */
class MenuDynamicSetting : public MenuSetting
{
public:
  MenuDynamicSetting();
  ~MenuDynamicSetting();
};

/*!
 * @class MenuEdit
 * @brief Input box, either used for key binding, or text input from user
 *
 *        This item is an input box to get a string from the user inside a Menu.
 */
class MenuEdit : public MenuItem
{
public:
  MenuEdit();
  ~MenuEdit();

  void onClick();
  
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);
};

/*!
 * @class MenuSlider
 * @brief Slider Setting item, accept any value within defined range
 *
 *        This item is a setting bar moving horizontally to get values from user.
 */
class MenuSlider : public MenuItem
{
public:
  MenuSlider();
  ~MenuSlider();

  void onClick();
  
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);
};


#endif
