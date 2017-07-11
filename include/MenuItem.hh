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
#include <unordered_map>
#include "Engine.hpp"

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
  void setPadding(const int &padding);
  virtual void setColor(const sf::Color &color);
  virtual void setFontsize(const int &size);
  virtual void setXOffset(const int &x);
  virtual void setYOffset(const int &y);
  virtual void setOffset(const int &x, const int &y);

  virtual bool onHover(const bool &triggered);
  virtual void onClick() = 0;

  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);

  static std::unordered_map<std::string, MenuItemType> typeMap; //move String to int ID
  
protected:
  Engine *_e;
  int _padding;
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

  void setCustomAction(void(*fptr)(void *), void *cparam);

  virtual void onClick();
  virtual bool onHover(const bool &triggered);

private:
  void (*_customPtr)(void *);
  void *_customParam;
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
  bool onValueHover(const bool &triggered);

  bool isValueHovered();
  virtual void setFontsize(const int &size);
  virtual void setXOffset(const int &x);
  virtual void setYOffset(const int &y);
  void setValues(std::vector<std::string> &values, const int &defaultIndex = 0);
  int getCurrentIndex();

  void updateValue();
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);

private:
  bool _vhover;
  sf::Text _value;
  std::vector<std::string> _values;
  size_t _index;
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

  virtual void setFontsize(const int &fontsize);
  virtual void setXOffset(const int &x);
  virtual void setYOffset(const int &y);
  void setInputLength(const int &length);

  void onClick();
  
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);
private:
	bool _focus;
	unsigned int _maxLength;
	std::string _input;
	sf::Text _value;
	sf::RectangleShape _container;
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

  void setRange(const int &min, const int &max);
  void setXOffset(const int &x);
  void setYOffset(const int &y);
  void setBarColor(const sf::Color *barColor, const sf::Color *fillColor);
  void setFontsize(const int &fontsize);

  int getValue();

  void onClick() {};

  void updateSlider(sf::Event &e);
  virtual bool update(sf::Event &e);
  virtual void draw(sf::RenderWindow *);
private:
	bool _sliding;
	int _value;
	int _range[2];
	sf::RectangleShape _bar, _fill;
};


#endif
