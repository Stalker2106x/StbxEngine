#include "MenuItem.hh"
#include "Resolver.hh"

/*
 * MenuItem Base class
 */

std::unordered_map<std::string, MenuItemType> MenuItem::typeMap = {
  {"Link", Link},
  {"Setting", Setting},
  {"DynamicSetting", DynamicSetting},
  {"Edit", Edit},
  {"Slider", Slider}
};

MenuItem::MenuItem()
{
  _hover = false;
  _label.setFont(*Resolver<sf::Font>::resolve("glitch"));
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

void MenuItem::setPadding(const int &padding)
{
	_padding = padding;
}

void MenuItem::setColor(const sf::Color &color)
{
  _label.setFillColor(color);
}

void MenuItem::setFontsize(const int &fontsize)
{
	_label.setCharacterSize(fontsize);
}

void MenuItem::setXOffset(const int &x)
{
	_label.setPosition(x, _label.getPosition().y);
}

void MenuItem::setYOffset(const int &y)
{
	_label.setPosition(_label.getPosition().x, y);
}

void MenuItem::setCustomAction(void (*fptr)(void))
{
  _customPtr = fptr;
}

void MenuItem::setOffset(const int &x, const int &y)
{
  _label.setPosition(x, y);
}

bool MenuItem::onHover(const bool &triggered)
{
	if ((triggered && _hover)
		|| (!triggered && !_hover))
		return (false);
	if (triggered)
		_hover = true;
	else
		_hover = false;
	return (true);
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
  else if (e.type == sf::Event::MouseButtonPressed && isHovered())
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

bool MenuLink::onHover(const bool &triggered)
{
	if (!MenuItem::onHover(triggered))
		return (false);
	sf::Color color = _label.getColor();

	color.r = ~color.r;
	color.g = ~color.g;
	color.b = ~color.b;
	if (triggered)
		_label.setColor(color);
	else
		_label.setColor(color);
	return (true);
}

/*
 * MenuSetting
 */

MenuSetting::MenuSetting() : MenuItem()
{
  _index = 0;
  _padding = 0;
  _value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

MenuSetting::~MenuSetting()
{

}

void MenuSetting::setFontsize(const int &fontsize)
{
	MenuItem::setFontsize(fontsize);
	_value.setCharacterSize(fontsize);
}

void MenuSetting::setXOffset(const int &x)
{
	MenuItem::setXOffset(x);
	_value.setPosition(x + _label.getLocalBounds().width + _padding, _value.getPosition().y);
}

void MenuSetting::setYOffset(const int &y)
{
	MenuItem::setYOffset(y);
	_value.setPosition(_value.getPosition().x, y);
}

void MenuSetting::setValues(std::vector<std::string> &values, const int &defaultIndex)
{
	_values = values;
	if (_values.size() > 0)
		_value.setString(_values[defaultIndex]);
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
	setRange(0, 100);
	_bar.setSize(sf::Vector2f(100, 10));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
	_bar.setFillColor(sf::Color(100, 250, 50));
	_fill.setFillColor(sf::Color(100, 0, 250));
}

void MenuSlider::setFontsize(const int &fontsize)
{
	MenuItem::setFontsize(fontsize);
	_bar.setSize(sf::Vector2f(_bar.getSize().x, _label.getGlobalBounds().height));
	_fill.setSize(sf::Vector2f(_bar.getSize().x - 2, _label.getGlobalBounds().height - 2));
}

void MenuSlider::setRange(const int &min, const int &max)
{
	_range[0] = min;
	_range[1] = max;
}

MenuSlider::~MenuSlider()
{

}

void MenuSlider::setXOffset(const int &x)
{
	MenuItem::setXOffset(x);
	_bar.setPosition(x + _label.getLocalBounds().width + _padding, _bar.getPosition().y);
	_fill.setPosition(x + _label.getLocalBounds().width + _padding + 1, _fill.getPosition().y);
}

void MenuSlider::setYOffset(const int &y)
{
	MenuItem::setYOffset(y);
	_bar.setPosition(_bar.getPosition().x, y);
	_fill.setPosition(_fill.getPosition().x, y + 1);
}

void MenuSlider::onClick()
{
	_value = sf::Mouse::getPosition(*Engine::instance->getWindowHandle()).x - _bar.getPosition().x;
	_fill.setSize(sf::Vector2f((_bar.getSize().x / _range[1]) * _value, _fill.getSize().y));
}

bool MenuSlider::update(sf::Event &e)
{
  MenuItem::update(e);
  if (e.type == sf::Event::MouseButtonPressed)
  {
	  if (_bar.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Engine::instance->getWindowHandle()))))
		  onClick();
  }
  return (true);
}

void MenuSlider::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
	win->draw(_bar);
	win->draw(_fill);
}
