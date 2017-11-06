#include "GUIEntity.hh"
#include "Engine.hpp"

using namespace stb;

//
// GUISIndicator
//

GUISIndicator::GUISIndicator(GUIElement *parent, const std::string &fontResource) : GUIElement("", parent, SIndicator)
{
}

GUISIndicator::~GUISIndicator()
{
	if (_label != NULL)
		delete (_label);
}

void GUISIndicator::initialUpdate()
{

}

void GUISIndicator::setFontsize(int fontSize)
{
	if (_label != NULL)
		_label->setCharacterSize(fontSize);
	_value.setCharacterSize(fontSize);
}

void GUISIndicator::setPosition(const sf::Vector2f &pos)
{
	if (_label != NULL)
		_label->setPosition(pos);
	_value.setPosition(_label->getPosition() + sf::Vector2f(_label->getLocalBounds().width + 5, 0));
}


const sf::Vector2f GUISIndicator::getPosition()
{
	return (_label->getPosition());
}

const sf::Vector2f GUISIndicator::getSize()
{
	return (sf::Vector2f(_label->getLocalBounds().width, _label->getLocalBounds().height));
}

bool GUISIndicator::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	return (true);
}

void GUISIndicator::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	if (_label != NULL)
		win->draw(*_label);
	win->draw(_value);
}

//
// GUIEdit
//

GUIEdit::GUIEdit(GUIElement *parent, char cursor, const std::string &fontResource) : GUIElement("", parent, Edit)
{
	_focus = false;
	_index = 0;
	setWidth(100);
	_cursor.setString(cursor);
	setFont(fontResource);
	setFontsize(Engine::instance->gui->defaults.fontSize);
}

GUIEdit::~GUIEdit()
{

}

void GUIEdit::initialUpdate()
{
}

void GUIEdit::setText(const std::string &text)
{
	_input = text;
	setCursorPos(text.size());
}

void GUIEdit::setFocus(bool focus)
{
	_focus = focus;
}

void GUIEdit::setFont(const std::string &fontResource)
{
	_value.setFont(*SFResolver<sf::Font>::resolve(fontResource));
	_cursor.setFont(*SFResolver<sf::Font>::resolve(fontResource));
	_container.setSize(sf::Vector2f(static_cast<float>(_container.getSize().x), static_cast<float>(_value.getCharacterSize())));
}

void GUIEdit::setFontsize(int fontsize)
{
	_value.setCharacterSize(fontsize);
	_cursor.setCharacterSize(fontsize);
	_container.setSize(sf::Vector2f(static_cast<float>(_container.getSize().x), static_cast<float>(_value.getCharacterSize())));
}

void GUIEdit::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
	_value.setPosition(pos + sf::Vector2f(1, 0));
	setCursorPos(_index);
}

void GUIEdit::setColor(sf::Color inputColor)
{
	_container.setFillColor(inputColor);
}

void GUIEdit::setTextColor(sf::Color textColor)
{
	_value.setFillColor(textColor);
	_cursor.setFillColor(textColor);
}

void GUIEdit::setCursorPos(int index)
{
	if (_index != index)
		_index = index;
	if (_input.empty())
		_cursor.setPosition(_value.getPosition());
	else
		_cursor.setPosition(_value.getPosition().x + 1 + ((_value.getLocalBounds().width / _input.length()) * index), _value.getPosition().y);
}

void GUIEdit::setWidth(const float &length)
{
	_container.setSize(sf::Vector2f(length, _container.getSize().y));
}

const sf::Vector2f GUIEdit::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f GUIEdit::getPosition()
{
	return (_container.getPosition());
}

int GUIEdit::getCursorPos()
{
	return (_index);
}


const std::string &GUIEdit::getText()
{
	return (_input);
}

void GUIEdit::clear()
{
	setCursorPos(0);
	_input.clear();
	_value.setString("");
}

bool GUIEdit::update(const sf::Event &e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
		{
			if (_container.getGlobalBounds().contains(Engine::getMousePosition()))
			{
				if (!_focus)
					_focus = true;
			}
			else if (_focus)
			{
				_focus = false;
			}
		}
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		if (_focus && e.key.code == sf::Keyboard::Left && _index > 0)
			_index--;
		else if (_focus && e.key.code == sf::Keyboard::Right && _index < _input.size())
			_index++;
	}
	if (_focus)
	{
		char c;

		c = Engine::getChar(e, alphanumeric);
		if (c == '\b')
		{
			if (_input.length() > 0 && _index > 0)
			{
				_input.erase(_input.begin() + (_index - 1));
				_index--;
			}
		}
		else if (c == '\n')
		{
			//do nothing...
		}
		else if (c != '\0')
		{
			_input.insert(_input.begin() + _index, c);
			_index++;
		}
		_value.setString(_input);
		setCursorPos(_index);
	}
	return (true);
}

void GUIEdit::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	win->draw(_value);
	if (_focus)
		win->draw(_cursor);
}


//
// GUISprite
//

GUISprite::GUISprite(GUIElement *parent, const std::string &resource) : GUIElement("", parent, Text)
{
	setTexture(resource);
}

GUISprite::~GUISprite()
{

}

void GUISprite::initialUpdate()
{

}

void GUISprite::setPosition(const sf::Vector2f &pos)
{
	_sprite.setPosition(pos);
}

void GUISprite::setTexture(const std::string &resource)
{
	_sprite.setTexture(*SFResolver<sf::Texture>::resolve(resource));
}

void GUISprite::setColor(sf::Color color)
{
	_sprite.setColor(color);
}

const sf::Vector2f GUISprite::getPosition()
{
	return (_sprite.getPosition());
}

const sf::Vector2f GUISprite::getSize()
{
	return (sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
}

bool GUISprite::update(const sf::Event &e)
{
	return (true);
}

void GUISprite::draw(sf::RenderWindow *win)
{
	win->draw(_sprite);
}


//
// GUIText
//

GUIText::GUIText(GUIElement *parent, const std::string &text, const std::string &fontResource) : GUIElement("", parent, Text)
{
	_text.setString(text);
	_text.setFont(*SFResolver<sf::Font>::resolve(fontResource));
}

GUIText::~GUIText()
{

}

void GUIText::initialUpdate()
{
}

void GUIText::setFont(const std::string &fontResource)
{
	_text.setFont(*SFResolver<sf::Font>::resolve(fontResource));
}

void GUIText::setFontSize(int fontsize)
{
	_text.setCharacterSize(fontsize);
}

void GUIText::setPosition(const sf::Vector2f &pos)
{
	_text.setPosition(pos);
}

void GUIText::setColor(sf::Color color)
{
	_text.setFillColor(color);
}

const sf::Vector2f GUIText::getPosition()
{
	return (_text.getPosition());
}

const sf::Vector2f GUIText::getSize()
{
	return (sf::Vector2f(_text.getLocalBounds().width, _text.getLocalBounds().height));
}

bool GUIText::update(const sf::Event &e)
{
	return (true);
}

void GUIText::draw(sf::RenderWindow *win)
{
	win->draw(_text);
}


//
// GUITextArea
//

GUITextArea::GUITextArea(GUIElement *parent) : GUIElement("", parent, TextArea)
{
	initialUpdate();
}

GUITextArea::~GUITextArea()
{

}

void GUITextArea::initialUpdate()
{
	_value.setFont(*SFResolver<sf::Font>::resolve("glitch"));
}

void GUITextArea::setFont(const std::string &fontResource)
{
	_value.setFont(*SFResolver<sf::Font>::resolve(fontResource));
}

void GUITextArea::setFontsize(int fontsize)
{
	_value.setCharacterSize(fontsize);
	_container.setSize(sf::Vector2f(static_cast<float>(_container.getSize().x), static_cast<float>(_value.getCharacterSize())));
}

void GUITextArea::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
	_value.setPosition(pos + sf::Vector2f(1, 0));
}

void GUITextArea::setColor(sf::Color *inputColor, sf::Color *valueColor)
{
	if (inputColor)
		_container.setFillColor(*inputColor);
	if (valueColor)
		_value.setFillColor(*valueColor);
}

void GUITextArea::setWidth(const float &length)
{
	_container.setSize(sf::Vector2f(length, _container.getSize().y));
}

const sf::Vector2f GUITextArea::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f GUITextArea::getPosition()
{
	return (_container.getPosition());
}

bool GUITextArea::update(const sf::Event &e)
{
	return (true);
}

void GUITextArea::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	win->draw(_value);
}


//
// GUICheckbox
//

GUICheckbox::GUICheckbox(GUIElement *parent) : GUIElement("", parent, Checkbox)
{
	initialUpdate();
}

GUICheckbox::~GUICheckbox()
{

}

void GUICheckbox::initialUpdate()
{
	_checked = false;
	_container.setSize(sf::Vector2f(20, 20));
	_container.setFillColor(sf::Color::White);
	_fill.setSize(sf::Vector2f(16, 16));
	_container.setFillColor(sf::Color::Black);
}

void GUICheckbox::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
	_fill.setPosition(pos + sf::Vector2f(2, 2));
}

void GUICheckbox::setColor(const sf::Color *containerColor, const sf::Color *fillColor)
{
	if (containerColor)
		_container.setFillColor(*containerColor);
	if (fillColor)
		_fill.setFillColor(*fillColor);
}

const sf::Vector2f GUICheckbox::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f GUICheckbox::getPosition()
{
	return (_container.getPosition());
}

bool GUICheckbox::update(const sf::Event &e)
{
	if (e.type == sf::Event::MouseButtonPressed && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
	{
		if (_container.getGlobalBounds().contains(Engine::getMousePosition()))
		{
			_checked = (_checked ? false : true);
		}
	}
	return (true);
}

void GUICheckbox::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	if (_checked)
		win->draw(_fill);
}


//
// GUISlider
//

GUISlider::GUISlider(GUIElement *parent) : GUIElement("", parent, Slider)
{
	setRange(0, 100);
	_bar.setSize(sf::Vector2f(102, 10));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
	_bar.setFillColor(sf::Color(100, 250, 50));
	_fill.setFillColor(sf::Color(100, 0, 250));
}

void GUISlider::setRange(int min, int max)
{
	_sliding = false;
	_range[0] = min;
	_range[1] = max;
}

GUISlider::~GUISlider()
{

}

void GUISlider::initialUpdate()
{

}

void GUISlider::setBarWidth(int width)
{
	_bar.setSize(sf::Vector2f(static_cast<float>(width), _bar.getSize().y));
	_fill.setSize(_bar.getSize() - sf::Vector2f(2, 2));
}

void GUISlider::setBarColor(const sf::Color *barColor, const sf::Color *fillColor)
{
	if (barColor != NULL)
		_bar.setFillColor(*barColor);
	if (fillColor != NULL)
		_fill.setFillColor(*fillColor);
}

void GUISlider::setPosition(const sf::Vector2f &pos)
{
	_bar.setPosition(pos);
	_fill.setPosition(pos + sf::Vector2f(1,1));
}

int GUISlider::getValue()
{
	return (_value);
}

const sf::Vector2f GUISlider::getSize()
{
	return (_bar.getSize());
}

const sf::Vector2f GUISlider::getPosition()
{
	return (_bar.getPosition());
}

void GUISlider::updateSlider(const sf::Event &e, bool forceupdate)
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

bool GUISlider::update(const sf::Event &e)
{
	if (!_active)
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

void GUISlider::draw(sf::RenderWindow *win)
{
	win->draw(_bar);
	win->draw(_fill);
}