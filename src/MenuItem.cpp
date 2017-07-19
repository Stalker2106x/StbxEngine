#include "MenuItem.hh"
#include "Resolver.hh"
#include "Menu.hh"

using namespace stb;

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
  _vhover = false;
  _padding = 0;
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

bool MenuItem::isValueHovered() const
{
	return (_vhover);
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

void MenuItem::setXOffset(const float &x)
{
	_label.setPosition(x, _label.getPosition().y);
}

void MenuItem::setYOffset(const float &y)
{
	_label.setPosition(_label.getPosition().x, y);
}

void MenuItem::setOffset(const float &x, const float &y)
{
  _label.setPosition(x, y);
}

void MenuItem::initialUpdate()
{
	if (_label.getGlobalBounds().contains(Engine::getMousePosition()))
		onHover(true);
	else
		onHover(false);
}

bool MenuItem::onValueHover(const bool &triggered)
{
	if ((triggered && _vhover)
		|| (!triggered && !_vhover))
		return (false);
	if (triggered)
		_vhover = true;
	else
		_vhover = false;
	return (true);
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
  else if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left && isHovered())
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
	_customPtr = NULL;
	_customParam = NULL;
	_customCommand = NULL;
}

MenuLink::~MenuLink()
{
	if (_customCommand)
		delete (_customCommand);
}

void MenuLink::setMenuHandle(Menu *menu)
{
	_menuHandle = menu;
}

void MenuLink::setTarget(const std::string &target)
{
	_target = target;
}

void MenuLink::setCustomAction(void(*fptr)(void *), void *cparam)
{
	_customPtr = fptr;
	_customParam = cparam;
}

void MenuLink::setCommand(const std::string &command)
{
	_customCommand = new std::string(command);
}


void MenuLink::onClick()
{
	if (_customPtr != NULL)
		_customPtr(_customParam);
	if (_customCommand != NULL)
		Commands::parseCmd(*stb::Engine::instance, *_customCommand);
	if (!_target.empty() && _menuHandle != NULL)
	{
		_menuHandle->reset();
		_menuHandle->loadFromFile("./Data/menu/" + _target + ".xml");
	}
	else
		Engine::console->output(COLOR_ERROR, "Menu: Link broken. action undefined.");
}

bool MenuLink::onHover(const bool &triggered)
{
	if (!MenuItem::onHover(triggered))
		return (false);
	sf::Color color = _label.getFillColor();

	color.r = ~color.r;
	color.g = ~color.g;
	color.b = ~color.b;
	_label.setFillColor(color);
	return (true);
}

/*
 * MenuSetting
 */

MenuSetting::MenuSetting() : MenuItem()
{
  _index = 0;
  _padding = 0;
  _hover = false;
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

void MenuSetting::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);
	_value.setPosition(x + _label.getLocalBounds().width + _padding, _value.getPosition().y);
}

void MenuSetting::setYOffset(const float &y)
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

int MenuSetting::getCurrentIndex()
{
	return (_index);
}

void MenuSetting::onClick()
{
  ++_index;
  if (_index >= _values.size())
	  _index = 0;
  updateValue();
}

void MenuSetting::onRClick()
{
  --_index;
  if (_index >= _values.size())
	  _index = _values.size() - 1;
  updateValue();
}

bool MenuSetting::onValueHover(const bool &triggered)
{
	if (!MenuItem::onValueHover(triggered))
		return (false);
	sf::Color color = _value.getFillColor();

	color.r = ~color.r;
	color.g = ~color.g;
	color.b = ~color.b;
	_value.setFillColor(color);
	return (true);
}

void MenuSetting::updateValue()
{
	if (_values.size() > 0)
		_value.setString(_values[_index]);
}

bool MenuSetting::update(sf::Event &e)
{
  MenuItem::update(e);
  if (e.type == sf::Event::MouseMoved)
  {
	  if (_value.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
		  onValueHover(true);
	  else
		  onValueHover(false);
  }
  else if (e.type == sf::Event::MouseButtonPressed && isValueHovered())
  {
	  if (e.key.code == sf::Mouse::Left)
		onClick();
	  else if (e.key.code == sf::Mouse::Right)
		onRClick();
  }
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
	_focus = false;
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

MenuEdit::~MenuEdit()
{

}

void MenuEdit::setFontsize(const int &fontsize)
{
	MenuItem::setFontsize(fontsize);
	_value.setCharacterSize(fontsize);
	_container.setSize(sf::Vector2f(_container.getSize().x, _label.getGlobalBounds().height));
}

void MenuEdit::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);

	_value.setPosition(x + _label.getLocalBounds().width + _padding + 1, _container.getPosition().y);
	_container.setPosition(x + _label.getLocalBounds().width + _padding, _container.getPosition().y);
}

void MenuEdit::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_value.setPosition(_container.getPosition().x, y + 1);
	_container.setPosition(_container.getPosition().x, y);
}

void MenuEdit::setColor(sf::Color *inputColor, sf::Color *valueColor)
{
	if (inputColor)
		_container.setFillColor(*inputColor);
	if (valueColor)
		_value.setFillColor(*valueColor);
}

void MenuEdit::setInputLength(const float &length)
{
	_container.setSize(sf::Vector2f(length, _container.getSize().y));
}

void MenuEdit::onClick()
{

}

bool MenuEdit::update(sf::Event &e)
{
  MenuItem::update(e);
  if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
  {
	  if (!_focus && _container.getGlobalBounds().contains(Engine::getMousePosition()))
	  {
		  _focus = true;
		  _input.push_back('.');
	  }
	  else if (_focus)
	  {
		  _focus = false;
		  _input.pop_back();
	  }
	  _value.setString(_input);
  }
  if (_focus)
  {
	  char c;
	  
	  c = Engine::getChar(e, alphanumeric);
	  if (c == '\b')
	  {
		  if (_input.length() > 1)
			_input.erase(_input.end() - 2);
	  }
	  else if (c == '\n')
	  {
		  _input.pop_back();
		  _focus = false;
	  }
	  else if (c != '\0')
	  {
		  _input.insert(_input.end() - 1, c);
	  }
	  _value.setString(_input);
  }
  return (true);
}

void MenuEdit::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
	win->draw(_container);
	win->draw(_value);
}
/*
 * MenuSlider
 */

MenuSlider::MenuSlider() : MenuItem()
{
	setRange(0, 100);
	_bar.setSize(sf::Vector2f(102, 10));
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
	_sliding = false;
	_range[0] = min;
	_range[1] = max;
}

MenuSlider::~MenuSlider()
{

}

void MenuSlider::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);
	_bar.setPosition(x + _label.getLocalBounds().width + _padding, _bar.getPosition().y);
	_fill.setPosition(x + _label.getLocalBounds().width + _padding + 1, _fill.getPosition().y);
}

void MenuSlider::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_bar.setPosition(_bar.getPosition().x, y);
	_fill.setPosition(_fill.getPosition().x, y + 1);
}

void MenuSlider::setBarWidth(const int &width)
{
	_bar.setSize(sf::Vector2f(width, _bar.getSize().y));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
}

void MenuSlider::setBarColor(const sf::Color *barColor, const sf::Color *fillColor)
{
	if (barColor != NULL)
		_bar.setFillColor(*barColor);
	if (fillColor != NULL)
		_fill.setFillColor(*fillColor);
}

int MenuSlider::getValue()
{
	return (_value);
}

void MenuSlider::updateSlider(sf::Event &e, bool forceupdate)
{
	if (_sliding && (e.type == sf::Event::MouseMoved || forceupdate))
	{
		_value = (Engine::getMousePosition().x - _bar.getPosition().x) * (_bar.getGlobalBounds().width / _range[1]);
		if (_value < _range[0])
			_value = _range[0];
		else if (_value > _range[1])
			_value = _range[1];
		if (Engine::getMousePosition().x - (_bar.getPosition().x + 1) >= _bar.getGlobalBounds().width - 1)
			_fill.setSize(sf::Vector2f(_bar.getGlobalBounds().width - 2, _fill.getSize().y));
		else if (Engine::getMousePosition().x - (_bar.getPosition().x + 1) < 0)
			_fill.setSize(sf::Vector2f(0, _fill.getSize().y));
		else
			_fill.setSize(sf::Vector2f(Engine::getMousePosition().x - (_bar.getPosition().x + 1), _fill.getSize().y));
	}
}

bool MenuSlider::update(sf::Event &e)
{
  MenuItem::update(e);
  updateSlider(e);
  if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
  {
	  if (_bar.getGlobalBounds().contains(Engine::getMousePosition()))
	  {
		  _sliding = true;
		  updateSlider(e, true);
	  }
  }
  else if (e.type == sf::Event::MouseButtonReleased && e.key.code == sf::Mouse::Left)
  {
		  _sliding = false;
  }
  return (true);
}

void MenuSlider::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
	win->draw(_bar);
	win->draw(_fill);
}
