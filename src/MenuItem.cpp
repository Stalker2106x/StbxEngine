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
  {"Slider", Slider},
  {"Checkbox", Checkbox}
};

MenuItem::MenuItem()
{
  _active = false;
  _padding = 0;
  _label = new GUITextButton();
  _label->setClickCallback(std::bind(&MenuItem::onClick, this));
  _mode = Text;
  if (_mode == Text)
	static_cast<GUITextButton *>(_label)->setFont(*Resolver<sf::Font>::resolve("glitch"));
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
	case Checkbox:
		return (new MenuCheckbox());
		break;
    }
  return (NULL);
}

void MenuItem::setLabel(const std::string &label)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setLabel(label);
}

void MenuItem::setPadding(const int &padding)
{
	_padding = padding;
}

void MenuItem::setColor(const sf::Color &color)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setColor(color);
}

void MenuItem::setFontsize(const int &fontsize)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setFontsize(fontsize);
}

void MenuItem::setXOffset(const float &x)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(x, _label->getPosition().y));
}

void MenuItem::setYOffset(const float &y)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(_label->getPosition().x, y));
}

void MenuItem::setOffset(const float &x, const float &y)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(x, y));
}

void MenuItem::initialUpdate()
{
	_active = true;
	_label->initialUpdate();
}

bool MenuItem::update(const sf::Event &e)
{
  if (!_active)
		return (false);
  _label->update(e);
  return (true);
}

void MenuItem::draw(sf::RenderWindow *win)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->draw(win);
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
		Engine::instance->console->output(COLOR_ERROR, "Menu: Link broken. action undefined.");
}

bool MenuLink::update(const sf::Event &e)
{
	if (!MenuItem::update(e))
		return (false);
	return (true);
}

/*
 * MenuSetting
 */

MenuSetting::MenuSetting() : MenuItem()
{
  _index = 0;
  _padding = 0;
  _value = new GUITextButton();
  _value->setFont(*Resolver<sf::Font>::resolve("glitch"));
  _value->setClickCallback(std::bind(&MenuSetting::onClick, this));
  _value->setRClickCallback(std::bind(&MenuSetting::onRClick, this));
}

MenuSetting::~MenuSetting()
{

}

void MenuSetting::setFontsize(const int &fontsize)
{
	MenuItem::setFontsize(fontsize);
	_value->setFontsize(fontsize);
}

void MenuSetting::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);
	_value->setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _value->getPosition().y));
}

void MenuSetting::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_value->setPosition(sf::Vector2f(_value->getPosition().x, y));
}

void MenuSetting::setValues(std::vector<std::string> &values, const int &defaultIndex)
{
	_values = values;
	if (_values.size() > 0)
		_value->setLabel(_values[defaultIndex]);
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

void MenuSetting::updateValue()
{
	if (_values.size() > 0)
		_value->setLabel(_values[_index]);
}

bool MenuSetting::update(const sf::Event &e)
{
	if (!MenuItem::update(e))
		return (false);
	_value->update(e);
  return (true);
}


void MenuSetting::draw(sf::RenderWindow *win)
{
  MenuItem::draw(win);
  _value->draw(win);
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
	_edit.setFont("glitch");
}

MenuEdit::~MenuEdit()
{

}

void MenuEdit::setFontsize(const int &fontsize)
{
	MenuItem::setFontsize(fontsize);
	_edit.setFontsize(fontsize);
}

void MenuEdit::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);
	_edit.setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _edit.getPosition().y));
}

void MenuEdit::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_edit.setPosition(sf::Vector2f(_edit.getPosition().x, y));
}

void MenuEdit::setInputColor(sf::Color *inputColor, sf::Color *valueColor)
{
	_edit.setColor(inputColor, valueColor);
}

void MenuEdit::setInputLength(const float &length)
{
	_edit.setWidth(length);
}

void MenuEdit::onClick()
{

}

bool MenuEdit::update(const sf::Event &e)
{
	if (!MenuItem::update(e))
		return (false);
	_edit.update(e);
  return (true);
}

void MenuEdit::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
	_edit.draw(win);
}

//
// MenuSlider
//

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
	_bar.setSize(sf::Vector2f(_bar.getSize().x, _label->getGlobalBounds().height));
	_fill.setSize(sf::Vector2f(_bar.getSize().x - 2, _label->getGlobalBounds().height - 2));
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
	_bar.setPosition(x + _label->getLocalBounds().width + _padding, _bar.getPosition().y);
	_fill.setPosition(x + _label->getLocalBounds().width + _padding + 1, _fill.getPosition().y);
}

void MenuSlider::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_bar.setPosition(_bar.getPosition().x, y);
	_fill.setPosition(_fill.getPosition().x, y + 1);
}

void MenuSlider::setBarWidth(const int &width)
{
	_bar.setSize(sf::Vector2f(static_cast<float>(width), _bar.getSize().y));
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

void MenuSlider::updateSlider(const sf::Event &e, bool forceupdate)
{
	if (_sliding && (e.type == sf::Event::MouseMoved || forceupdate))
	{
		_value = static_cast<int>((Engine::getMousePosition().x - _bar.getPosition().x) * (_bar.getGlobalBounds().width / _range[1]));
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

bool MenuSlider::update(const sf::Event &e)
{
	if (!MenuItem::update(e))
		return (false);
  updateSlider(e);
  if (e.type == sf::Event::MouseButtonPressed && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
  {
	  if (_bar.getGlobalBounds().contains(Engine::getMousePosition()))
	  {
		  _sliding = true;
		  updateSlider(e, true);
	  }
  }
  else if (e.type == sf::Event::MouseButtonReleased && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
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

//
// MenuCheckbox
//

MenuCheckbox::MenuCheckbox() : MenuItem()
{
}

MenuCheckbox::~MenuCheckbox()
{

}

void MenuCheckbox::setXOffset(const float &x)
{
	MenuItem::setXOffset(x);
	_checkBox.setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _checkBox.getPosition().y));
}

void MenuCheckbox::setYOffset(const float &y)
{
	MenuItem::setYOffset(y);
	_checkBox.setPosition(sf::Vector2f(_checkBox.getPosition().x, y));
}

void MenuCheckbox::setCheckboxColor(const sf::Color *containerColor, const sf::Color *fillColor)
{
	_checkBox.setColor(containerColor, fillColor);
}

bool MenuCheckbox::update(const sf::Event &e)
{
	if (!MenuItem::update(e))
		return (false);
	_checkBox.update(e);
	return (true);
}

void MenuCheckbox::draw(sf::RenderWindow *win)
{
	MenuItem::draw(win);
	_checkBox.draw(win);
}
