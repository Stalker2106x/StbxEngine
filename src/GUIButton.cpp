#include "GUIButton.hh"
#include "Engine.hpp"
#include "Resolver.hh"

using namespace stb;

//
// GUIButton
//

GUIButton::GUIButton(GUIElement *parent, const sf::Event::EventType &triggerType) : GUIElement("", parent, Button)
{
	_onClickCallback = NULL;
	_onRClickCallback = NULL;
	_triggerType = triggerType;
}

GUIButton::~GUIButton()
{
}

void GUIButton::initialUpdate()
{
	_hover = false;
	/*if (_skin->type == SkinSprite)
		setActiveSkin(static_cast<SpriteSkin *>(_skin)->normal);
	else if (_skin->type == SkinText)
		setActiveSkin(static_cast<TextSkin *>(_skin)->normal);*/ //tmp
}

bool GUIButton::isHovered() const
{
	return (_hover);
}

void GUIButton::setCommand(const std::string &command)
{
	_command = command;
}

void GUIButton::setClickCallback(const std::function<void(void)> &fptr)
{
	_onClickCallback = new std::function<void(void)>(fptr);
}

void GUIButton::setRClickCallback(const std::function<void(void)> &fptr)
{
	_onRClickCallback = new std::function<void(void)>(fptr);
}

void GUIButton::setSkin(Skin *skin)
{
	_skin = skin;
	if (_skin->type == SkinText)
	{
			setActiveSkin(static_cast<TextSkin *>(_skin)->text, static_cast<TextSkin *>(_skin)->normal);
	}
	else if (_skin->type == SkinSprite)
	{
			setActiveSkin(static_cast<SpriteSkin *>(_skin)->normal);
	}
}

bool GUIButton::onHover(bool triggered)
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

void GUIButton::onClick()
{
	if (!_command.empty())
		Commands::parseCmd(*Engine::instance, _command);
	else
	{
		if (_onClickCallback != NULL)
			(*_onClickCallback)();
	}
}

void GUIButton::onRClick()
{
	if (_onRClickCallback != NULL)
		(*_onRClickCallback)();
}

bool GUIButton::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	if (e.type == _triggerType && _hover)
	{
		if (static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
			onClick();
		else if (static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Right))
			onRClick();
	}
	return (true);
}

//
// GUIToggleSpriteButton
//

GUIToggleButton::GUIToggleButton(GUIElement *parent, const sf::Event::EventType &triggerType) : GUIButton(parent, triggerType)
{
	_state = false;
}

GUIToggleButton::~GUIToggleButton()
{
}

void GUIToggleButton::initialUpdate()
{
	GUIButton::initialUpdate();
}

void GUIToggleButton::setAltSkin(Skin *altSkin)
{
	_altSkin = altSkin;
}

bool GUIToggleButton::onHover(bool triggered) //Set correct skin based on type of btn
{
	GUIButton::onHover(triggered);
	if (triggered)
	{
		if (_altSkin->type == SkinText)
		{
			if (_state)
				setActiveSkin(static_cast<TextSkin *>(_altSkin)->text, static_cast<TextSkin *>(_altSkin)->hover);
			else
				setActiveSkin(static_cast<TextSkin *>(_skin)->text, static_cast<TextSkin *>(_skin)->hover);
		}
		else if (_altSkin->type == SkinSprite)
		{
			if (_state)
				setActiveSkin(static_cast<SpriteSkin *>(_altSkin)->hover);
			else
				setActiveSkin(static_cast<SpriteSkin *>(_skin)->hover);
		}
	}
	else
	{
		if (_altSkin->type == SkinText)
		{
			if (_state)
				setActiveSkin(static_cast<TextSkin *>(_altSkin)->text, static_cast<TextSkin *>(_altSkin)->normal);
			else
				setActiveSkin(static_cast<TextSkin *>(_skin)->text, static_cast<TextSkin *>(_skin)->normal);
		}
		else if (_altSkin->type == SkinSprite)
		{
			if (_state)
				setActiveSkin(static_cast<SpriteSkin *>(_altSkin)->normal);
			else
				setActiveSkin(static_cast<SpriteSkin *>(_skin)->normal);
		}
	}
	return (true);
}

void GUIToggleButton::onClick()
{
	_state = (_state ? false : true);
	onHover(true);
	GUIButton::onClick();
}

bool GUIToggleButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	return (true);
}

//
// GUISettingButton
//

GUISettingButton::GUISettingButton(GUIElement *parent, const sf::Event::EventType &triggerType) : GUIButton(parent, triggerType)
{
	_index = 0;
	setClickCallback(std::bind(&GUISettingButton::click, this));
	setRClickCallback(std::bind(&GUISettingButton::RClick, this));
}

GUISettingButton::~GUISettingButton()
{

}

void GUISettingButton::initialUpdate()
{
	GUIButton::initialUpdate();
}

void GUISettingButton::setValues(std::vector<std::string> &values, int defaultIndex)
{
	_values = values;
	/*if (_values.size() > 0)
		setLabel(_values[defaultIndex]);*/ //TMP
}

void GUISettingButton::pushValue(const std::string &value)
{
	_values.push_back(value);
}

int GUISettingButton::getCurrentIndex()
{
	return (_index);
}

void GUISettingButton::click()
{
	++_index;
	if (_index >= _values.size())
		_index = 0;
	updateValue();
}

void GUISettingButton::RClick()
{
	--_index;
	if (_index >= _values.size())
		_index = _values.size() - 1;
	updateValue();
}

void GUISettingButton::updateValue()
{
	if (_values.size() > 0)
		setLabel(_values[_index]);
}

//
// GUIButtonBar
//

GUIButtonBar::GUIButtonBar(GUIElement *parent, BarType type) : GUIElement("", parent, ButtonBar)
{
	_spacing = 0;
	_type = type;
	_inverted = false;
}

GUIButtonBar::~GUIButtonBar()
{

}

void GUIButtonBar::initialUpdate()
{

}

void GUIButtonBar::invert()
{
	_inverted = (_inverted ? false : true);
}

GUIButton *GUIButtonBar::getButton(const std::string &id)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		if ((*it)->getId() == id)
			return (*it);
		it++;
	}
	return (NULL);
}

const sf::Vector2f GUIButtonBar::getSize()
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();
	sf::Vector2f size(0,0);

	while (it != _buttons.end())
	{
		if (_type == Horizontal)
		{
			size.x += (*it)->getSize().x;
			if (size.y < (*it)->getSize().y)
				size.y = (*it)->getSize().y;
		}
		else if (_type == Vertical)
		{
			size.y += (*it)->getSize().y;
			if (size.x < (*it)->getSize().x)
				size.x = (*it)->getSize().x;
		}
		it++;
	}
	return (size);
}

void GUIButtonBar::setSpacing(int spacing)
{
	_spacing = spacing;
}

const sf::Vector2f GUIButtonBar::calcButtonPosition(const size_t &index, const sf::Vector2f &pos)
{
	float size = 0;

	for (int i = index + (_inverted ? 1 : -1 ); (_inverted ? i < static_cast<int>(_buttons.size()) : i >= 0); (_inverted ? i++ : i--))
	{
		if (_type == Horizontal)
		{
			size += _buttons[i]->getSize().x + _spacing;
		}
		else if (_type == Vertical)
		{
			size += _buttons[i]->getSize().y + _spacing;
		}
	}
	if (_type == Vertical)
		return (pos + sf::Vector2f(0, size));
	return (pos + sf::Vector2f(size, 0)); //Horizontal
}

void GUIButtonBar::setPosition(const sf::Vector2f &pos)
{
	for (int i = (_inverted ? _buttons.size() - 1 : 0); (_inverted ? i >= 0 : i < static_cast<int>(_buttons.size())); (_inverted ? i-- : i++))
		_buttons[i]->setPosition(calcButtonPosition(i, pos));
}

const sf::Vector2f GUIButtonBar::getPosition()
{
	return (_buttons.size() > 0 ? _buttons[0]->getPosition() : sf::Vector2f(0,0));
}

GUIButton *GUIButtonBar::addButton(GUIButton *button)
{
	_buttons.push_back(button);
	return (button);
}

bool GUIButtonBar::update(const sf::Event &e)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->update(e);
		it++;
	}
	return (true);
}

void GUIButtonBar::draw(sf::RenderWindow *win)
{
	std::vector<GUIButton *>::iterator it = _buttons.begin();

	while (it != _buttons.end())
	{
		(*it)->draw(win);
		it++;
	}
}