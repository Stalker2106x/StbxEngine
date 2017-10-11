#include "GUIEntity.hh"
#include "Engine.hpp"

using namespace stb;

//
// GUISIndicator
//

GUISIndicator::GUISIndicator(const std::string &label) : GUIElement(label)
{
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

GUISIndicator::~GUISIndicator()
{
	if (_label != NULL)
		delete (_label);
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


const sf::Vector2f &GUISIndicator::getPosition()
{
	return (_label->getPosition());
}

bool GUISIndicator::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
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

GUIEdit::GUIEdit(const std::string &id) : GUIElement(id)
{
	initialUpdate();
}

GUIEdit::~GUIEdit()
{

}

void GUIEdit::initialUpdate()
{
	_focus = false;
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

void GUIEdit::setFont(const std::string &fontResource)
{
	_value.setFont(*Resolver<sf::Font>::resolve(fontResource));
}

void GUIEdit::setFontsize(int fontsize)
{
	_value.setCharacterSize(fontsize);
	_container.setSize(sf::Vector2f(static_cast<float>(_container.getSize().x), static_cast<float>(_value.getCharacterSize())));
}

void GUIEdit::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
	_value.setPosition(pos + sf::Vector2f(1, 0));
}

void GUIEdit::setColor(sf::Color *inputColor, sf::Color *valueColor)
{
	if (inputColor)
		_container.setFillColor(*inputColor);
	if (valueColor)
		_value.setFillColor(*valueColor);
}

void GUIEdit::setWidth(const float &length)
{
	_container.setSize(sf::Vector2f(length, _container.getSize().y));
}

const sf::Vector2f &GUIEdit::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f &GUIEdit::getPosition()
{
	return (_container.getPosition());
}

const std::string &GUIEdit::getInput()
{
	return (_input);
}

bool GUIEdit::update(const sf::Event &e)
{
	if (e.type == sf::Event::MouseButtonPressed && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
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

void GUIEdit::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	win->draw(_value);
}


//
// GUITextArea
//

GUITextArea::GUITextArea(const std::string &id) : GUIElement(id)
{
	initialUpdate();
}

GUITextArea::~GUITextArea()
{

}

void GUITextArea::initialUpdate()
{
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

void GUITextArea::setFont(const std::string &fontResource)
{
	_value.setFont(*Resolver<sf::Font>::resolve(fontResource));
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

const sf::Vector2f &GUITextArea::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f &GUITextArea::getPosition()
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
// GUIText
//

GUIText::GUIText(const std::string &id) : GUIElement(id)
{
	initialUpdate();
}

GUIText::~GUIText()
{

}

void GUIText::initialUpdate()
{
	_value.setFont(*Resolver<sf::Font>::resolve("glitch"));
}

void GUIText::setFont(const std::string &fontResource)
{
	_value.setFont(*Resolver<sf::Font>::resolve(fontResource));
}

void GUIText::setFontsize(int fontsize)
{
	_value.setCharacterSize(fontsize);
	_container.setSize(sf::Vector2f(static_cast<float>(_container.getSize().x), static_cast<float>(_value.getCharacterSize())));
}

void GUIText::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
	_value.setPosition(pos + sf::Vector2f(1, 0));
}

void GUIText::setColor(sf::Color *inputColor, sf::Color *valueColor)
{
	if (inputColor)
		_container.setFillColor(*inputColor);
	if (valueColor)
		_value.setFillColor(*valueColor);
}

void GUIText::setWidth(const float &length)
{
	_container.setSize(sf::Vector2f(length, _container.getSize().y));
}

const sf::Vector2f &GUIText::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f &GUIText::getPosition()
{
	return (_container.getPosition());
}

bool GUIText::update(const sf::Event &e)
{
	return (true);
}

void GUIText::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	win->draw(_value);
}

//
// GUICheckbox
//

GUICheckbox::GUICheckbox(const std::string &id) : GUIElement(id)
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

const sf::Vector2f &GUICheckbox::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f &GUICheckbox::getPosition()
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