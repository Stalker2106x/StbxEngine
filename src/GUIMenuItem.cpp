#include "GUIMenuItem.hh"
#include "GUIMenu.hh"
#include "Resolver.hh"

using namespace stb;

/*
 * GUIMenuItem Base class
 */

std::unordered_map<std::string, GUIMenuItemType> GUIMenuItem::typeMap = {
  {"Link", Link},
  {"Setting", Setting},
  {"DynamicSetting", DynamicSetting},
  {"Edit", Edit},
  {"Slider", Slider},
  {"Checkbox", Checkbox}
};

GUIMenuItem::GUIMenuItem()
{
  _active = false;
  _padding = 0;
  _label = new GUITextButton();
  _label->setClickCallback(std::bind(&GUIMenuItem::onClick, this));
  _mode = Text;
  if (_mode == Text)
	static_cast<GUITextButton *>(_label)->setFont(*Resolver<sf::Font>::resolve("glitch"));
}

GUIMenuItem::~GUIMenuItem()
{

}

GUIMenuItem *GUIMenuItem::factory(const GUIMenuItemType &type)
{
  switch (type)
    {
    case Link:
		return (new GUIMenuLink());
		break;
    case Setting:
		return (new GUIMenuSetting());
		break;
    case DynamicSetting:
		return (new GUIMenuDynamicSetting());
		break;
    case Edit:
		return (new GUIMenuEdit());
		break;
    case Slider:
		return (new GUIMenuSlider());
		break;
	case Checkbox:
		return (new GUIMenuCheckbox());
		break;
    }
  return (NULL);
}

void GUIMenuItem::setLabel(const std::string &label)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setLabel(label);
}

void GUIMenuItem::setPadding(int padding)
{
	_padding = padding;
}

void GUIMenuItem::setColor(const sf::Color &color)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setColor(color);
}

void GUIMenuItem::setFontsize(int fontsize)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setFontsize(fontsize);
}

void GUIMenuItem::setPosition(const sf::Vector2f &pos)
{
	setOffset(pos.x, pos.y);
}

void GUIMenuItem::setXOffset(const float &x)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(x, _label->getPosition().y));
}

void GUIMenuItem::setYOffset(const float &y)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(_label->getPosition().x, y));
}

void GUIMenuItem::setOffset(const float &x, const float &y)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->setPosition(sf::Vector2f(x, y));
}

int &GUIMenuItem::getPadding()
{
	return (_padding);
}

const sf::Vector2f &GUIMenuItem::getPosition()
{
	if (_mode == Text)
		return (static_cast<GUITextButton *>(_label)->getPosition());
}

void GUIMenuItem::initialUpdate()
{
	_active = true;
	_label->initialUpdate();
}

bool GUIMenuItem::update(const sf::Event &e)
{
  if (!_active)
		return (false);
  _label->update(e);
  return (true);
}

void GUIMenuItem::draw(sf::RenderWindow *win)
{
	if (_mode == Text)
		static_cast<GUITextButton *>(_label)->draw(win);
}

/*
 * GUIMenuLink
 */

GUIMenuLink::GUIMenuLink() : GUIMenuItem()
{
	_customPtr = NULL;
	_customParam = NULL;
	_customCommand = NULL;
}

GUIMenuLink::~GUIMenuLink()
{
	if (_customCommand)
		delete (_customCommand);
}

void GUIMenuLink::setMenuHandle(GUIMenu *GUIMenu)
{
	_menuHandle = GUIMenu;
}

void GUIMenuLink::setTarget(const std::string &target)
{
	_target = target;
}

void GUIMenuLink::setCustomAction(void(*fptr)(void *), void *cparam)
{
	_customPtr = fptr;
	_customParam = cparam;
}

void GUIMenuLink::setCommand(const std::string &command)
{
	_customCommand = new std::string(command);
}


void GUIMenuLink::onClick()
{
	if (_customPtr != NULL)
		_customPtr(_customParam);
	if (_customCommand != NULL)
		Commands::parseCmd(*stb::Engine::instance, *_customCommand);
	if (!_target.empty() && _menuHandle != NULL)
	{
		_menuHandle->reset();
		_menuHandle->changeScreen("./Data/GUIMenu/" + _target + ".xml");
	}
	else
		Engine::instance->console->output(COLOR_ERROR, "GUIMenu: Link broken. action undefined.");
}

bool GUIMenuLink::update(const sf::Event &e)
{
	if (!GUIMenuItem::update(e))
		return (false);
	return (true);
}

/*
 * GUIMenuSetting
 */

GUIMenuSetting::GUIMenuSetting() : GUIMenuItem()
{
  _index = 0;
  _padding = 0;
  _value = new GUITextButton();
  _value->setFont(*Resolver<sf::Font>::resolve("glitch"));
  _value->setClickCallback(std::bind(&GUIMenuSetting::onClick, this));
  _value->setRClickCallback(std::bind(&GUIMenuSetting::onRClick, this));
}

GUIMenuSetting::~GUIMenuSetting()
{

}

void GUIMenuSetting::setFontsize(int fontsize)
{
	GUIMenuItem::setFontsize(fontsize);
	_value->setFontsize(fontsize);
}

void GUIMenuSetting::setXOffset(const float &x)
{
	GUIMenuItem::setXOffset(x);
	_value->setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _value->getPosition().y));
}

void GUIMenuSetting::setYOffset(const float &y)
{
	GUIMenuItem::setYOffset(y);
	_value->setPosition(sf::Vector2f(_value->getPosition().x, y));
}

void GUIMenuSetting::setValues(std::vector<std::string> &values, int defaultIndex)
{
	_values = values;
	if (_values.size() > 0)
		_value->setLabel(_values[defaultIndex]);
}

int GUIMenuSetting::getCurrentIndex()
{
	return (_index);
}

void GUIMenuSetting::onClick()
{
  ++_index;
  if (_index >= _values.size())
	  _index = 0;
  updateValue();
}

void GUIMenuSetting::onRClick()
{
  --_index;
  if (_index >= _values.size())
	  _index = _values.size() - 1;
  updateValue();
}

void GUIMenuSetting::updateValue()
{
	if (_values.size() > 0)
		_value->setLabel(_values[_index]);
}

bool GUIMenuSetting::update(const sf::Event &e)
{
	if (!GUIMenuItem::update(e))
		return (false);
	_value->update(e);
  return (true);
}


void GUIMenuSetting::draw(sf::RenderWindow *win)
{
  GUIMenuItem::draw(win);
  _value->draw(win);
}

/*
 * GUIMenuDynamicSetting
 */

GUIMenuDynamicSetting::GUIMenuDynamicSetting() : GUIMenuSetting()
{

}

GUIMenuDynamicSetting::~GUIMenuDynamicSetting()
{

}

/*
 * GUIMenuEdit
 */

GUIMenuEdit::GUIMenuEdit() : GUIMenuItem()
{
	_edit.setFont("glitch");
}

GUIMenuEdit::~GUIMenuEdit()
{

}

void GUIMenuEdit::setFontsize(int fontsize)
{
	GUIMenuItem::setFontsize(fontsize);
	_edit.setFontsize(fontsize);
}

void GUIMenuEdit::setXOffset(const float &x)
{
	GUIMenuItem::setXOffset(x);
	_edit.setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _edit.getPosition().y));
}

void GUIMenuEdit::setYOffset(const float &y)
{
	GUIMenuItem::setYOffset(y);
	_edit.setPosition(sf::Vector2f(_edit.getPosition().x, y));
}

void GUIMenuEdit::setInputColor(sf::Color *inputColor, sf::Color *valueColor)
{
	_edit.setColor(inputColor, valueColor);
}

void GUIMenuEdit::setInputLength(const float &length)
{
	_edit.setWidth(length);
}

void GUIMenuEdit::onClick()
{

}

bool GUIMenuEdit::update(const sf::Event &e)
{
	if (!GUIMenuItem::update(e))
		return (false);
	_edit.update(e);
  return (true);
}

void GUIMenuEdit::draw(sf::RenderWindow *win)
{
	GUIMenuItem::draw(win);
	_edit.draw(win);
}

//
// GUIMenuSlider
//

GUIMenuSlider::GUIMenuSlider() : GUIMenuItem()
{
	setRange(0, 100);
	_bar.setSize(sf::Vector2f(102, 10));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
	_bar.setFillColor(sf::Color(100, 250, 50));
	_fill.setFillColor(sf::Color(100, 0, 250));
}

void GUIMenuSlider::setFontsize(int fontsize)
{
	GUIMenuItem::setFontsize(fontsize);
	_bar.setSize(sf::Vector2f(_bar.getSize().x, _label->getGlobalBounds().height));
	_fill.setSize(sf::Vector2f(_bar.getSize().x - 2, _label->getGlobalBounds().height - 2));
}

void GUIMenuSlider::setRange(int min, int max)
{
	_sliding = false;
	_range[0] = min;
	_range[1] = max;
}

GUIMenuSlider::~GUIMenuSlider()
{

}

void GUIMenuSlider::setXOffset(const float &x)
{
	GUIMenuItem::setXOffset(x);
	_bar.setPosition(x + _label->getLocalBounds().width + _padding, _bar.getPosition().y);
	_fill.setPosition(x + _label->getLocalBounds().width + _padding + 1, _fill.getPosition().y);
}

void GUIMenuSlider::setYOffset(const float &y)
{
	GUIMenuItem::setYOffset(y);
	_bar.setPosition(_bar.getPosition().x, y);
	_fill.setPosition(_fill.getPosition().x, y + 1);
}

void GUIMenuSlider::setBarWidth(int width)
{
	_bar.setSize(sf::Vector2f(static_cast<float>(width), _bar.getSize().y));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
}

void GUIMenuSlider::setBarColor(const sf::Color *barColor, const sf::Color *fillColor)
{
	if (barColor != NULL)
		_bar.setFillColor(*barColor);
	if (fillColor != NULL)
		_fill.setFillColor(*fillColor);
}

int GUIMenuSlider::getValue()
{
	return (_value);
}

void GUIMenuSlider::updateSlider(const sf::Event &e, bool forceupdate)
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

bool GUIMenuSlider::update(const sf::Event &e)
{
	if (!GUIMenuItem::update(e))
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

void GUIMenuSlider::draw(sf::RenderWindow *win)
{
	GUIMenuItem::draw(win);
	win->draw(_bar);
	win->draw(_fill);
}

//
// GUIMenuCheckbox
//

GUIMenuCheckbox::GUIMenuCheckbox() : GUIMenuItem()
{
}

GUIMenuCheckbox::~GUIMenuCheckbox()
{

}

void GUIMenuCheckbox::setXOffset(const float &x)
{
	GUIMenuItem::setXOffset(x);
	_checkBox.setPosition(sf::Vector2f(x + _label->getLocalBounds().width + _padding, _checkBox.getPosition().y));
}

void GUIMenuCheckbox::setYOffset(const float &y)
{
	GUIMenuItem::setYOffset(y);
	_checkBox.setPosition(sf::Vector2f(_checkBox.getPosition().x, y));
}

void GUIMenuCheckbox::setCheckboxColor(const sf::Color *containerColor, const sf::Color *fillColor)
{
	_checkBox.setColor(containerColor, fillColor);
}

bool GUIMenuCheckbox::update(const sf::Event &e)
{
	if (!GUIMenuItem::update(e))
		return (false);
	_checkBox.update(e);
	return (true);
}

void GUIMenuCheckbox::draw(sf::RenderWindow *win)
{
	GUIMenuItem::draw(win);
	_checkBox.draw(win);
}
