#include "MenuItem.hh"
#include "Resolver.hh"

/*
 * MenuItem Base class
 */

std::map<std::string, MenuItemType> MenuItem::typeMap = {
  {"Link", Link},
  {"Setting", Setting},
  {"DynamicSetting", DynamicSetting},
  {"Edit", Edit},
  {"Slider", Slider}
};

MenuItem::MenuItem()
{
  _hover = false;
  _label.setFont(*Resolver::resolve<sf::Font>("console"));
}

MenuItem::~MenuItem()
{

}

MenuItem *MenuItem::factory(const MenuItemType &type)
{
  switch (type)
    {
    case Link:
      return (new MenuLink());
      break;
    case Setting:
      return (new MenuSetting());
      break;
    case DynamicSetting:
      return (new MenuDynamicSetting());
      break;
    case Edit:
      return (new MenuEdit());
      break;
    case Slider:
      return (new MenuSlider());
      break;
    }
  return (NULL);
}

bool MenuItem::isHovered() const
{
  return (_hover);
}

void MenuItem::setLabel(const std::string &label)
{
  _label.setString(label);
}

void MenuItem::setColor(const sf::Color &color)
{
  _label.setFillColor(color);
}

void MenuItem::setCustomAction(void (*fptr)(void))
{
  _customPtr = fptr;
}

void MenuItem::setPosition(const sf::Vector2f &pos)
{
  _label.setPosition(pos.x, pos.y);
}

void MenuItem::onHover(bool triggered)
{
	if ((triggered && _hover)
		|| (!triggered && !_hover))
		return;
	sf::Color color = _label.getColor();

	color.r = ~color.r;
	color.g = ~color.g;
	color.b = ~color.b;
	if (triggered)
	{
		if (!_hover)
			_label.setColor(color);
		_hover = true;
	}
	else
	{
		if (_hover)
			_label.setColor(color);
		_hover = false;
	}
}

bool MenuItem::update(sf::Event &e)
{
  if (e.type == sf::Event::MouseMoved)
    {
		if (_label.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
			onHover(true);
		else
			onHover(false);
    }
  else if (e.type == sf::Event::MouseButtonPressed)
    {
      onClick();
    }
  return (true);
}

void MenuItem::draw(sf::RenderWindow *win)
{
  win->draw(_label);
}

/*
 * MenuLink
 */

MenuLink::MenuLink() : MenuItem()
{

}

MenuLink::~MenuLink()
{

}

void MenuLink::onClick()
{

}

/*
 * MenuSetting
 */

MenuSetting::MenuSetting() : MenuItem()
{
  _index = 0;
}

MenuSetting::~MenuSetting()
{

}

void MenuSetting::onClick()
{
  ++_index;
  if (_index >= _values.size())
    _index = 0;
}

void MenuSetting::onRClick()
{
  --_index;
  if (_index < 0)
    _index = _values.size() - 1;
}

void MenuSetting::setValues(std::vector<std::string> &values, const int &defaultIndex)
{
  _values = values;
  if (_values.size() > 0)
    _value.setString(_values[defaultIndex]);
}

bool MenuSetting::update(sf::Event &e)
{
  MenuItem::update(e);
  return (true);
}


void MenuSetting::draw(sf::RenderWindow *win)
{
  MenuItem::draw(win);
  win->draw(_value);
}

/*
 * MenuDynamicSetting
 */

MenuDynamicSetting::MenuDynamicSetting() : MenuSetting()
{

}

MenuDynamicSetting::~MenuDynamicSetting()
{

}

/*
 * MenuEdit
 */

MenuEdit::MenuEdit() : MenuItem()
{

}

MenuEdit::~MenuEdit()
{

}

void MenuEdit::onClick()
{

}

bool MenuEdit::update(sf::Event &e)
{
  MenuItem::update(e);
  return (true);
}

void MenuEdit::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
}
/*
 * MenuSlider
 */

MenuSlider::MenuSlider() : MenuItem()
{

}

MenuSlider::~MenuSlider()
{

}

void MenuSlider::onClick()
{

}

bool MenuSlider::update(sf::Event &e)
{
  MenuItem::update(e);
  return (true);
}

void MenuSlider::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
}
