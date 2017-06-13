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

/*!
 * @class MenuItem
 * @brief Abstract Menu item
 *
 *        This class is not instanciable. It is used as an abstract layer to store Items generically in Menu class.
 */
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

/*!
 * @class MenuLink
 * @brief Menu link to another menu or action
 *
 *        Link defines a MenuItem that is clickable and points towards another menu or do a specific action (quit, apply settings, ...)
 */
class MenuLink : public MenuItem
{

};

/*!
 * @class MenuSetting
 * @brief Static Setting item, showing a list of values defined in XML.
 *
 *        This class holds a static enum defined in XML, for dynamic values, use child MenuDynamicSetting
 */
class MenuSetting : public MenuItem
{

};

/*!
 * @class MenuDynamicSetting
 * @brief Dynamic Setting item, showing a list of values known only at runtime.
 *
 *        This class holds a dynamic enum filled at runtime, for static values, use parent MenuSetting
 */
class MenuDynamicSetting : public MenuSetting
{

};

/*!
 * @class MenuEdit
 * @brief Input box, either used for key binding, or text input from user
 *
 *        This item is an input box to get a string from the user inside a Menu.
 */
class MenuEdit : public MenuItem
{

};



#endif
