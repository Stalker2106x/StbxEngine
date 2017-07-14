#include "HUDElement.hh"
#include "Engine.hpp"
#include "Resolver.hh"

//
// HUDElement
//

HUDElement::HUDElement()
{
	_active = true;
}

void HUDElement::toggle()
{
	_active = (_active ? false : true);
}

//
// HUDSIndicator
//
HUDSIndicator::HUDSIndicator(std::string *label)
{
	_label = NULL;
	_active = true;
	if (label != NULL)
	{
		_label = new sf::Text();
		_label->setString(*label);
		delete (label);
	}
}

HUDSIndicator::~HUDSIndicator()
{
	if (_label != NULL)
		delete (_label);
}

void HUDSIndicator::setFontsize(const int &fontSize)
{
	if (_label != NULL)
		_label->setCharacterSize(fontSize);
	_value.setCharacterSize(fontSize);
}

void HUDSIndicator::setPosition(const sf::Vector2f &pos)
{
	_label->setPosition(pos);
	_value.setPosition(_label->getPosition() + sf::Vector2f(_label->getLocalBounds().width + 5, 0));
}

bool HUDSIndicator::update(const sf::Event &e)
{
	return (true);
}

void HUDSIndicator::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(*_label);
	win->draw(_value);
}

//
// HUDPanel
//

HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color)
{
	sf::Texture ctexture;

	_frame.setPosition(pos);
	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &name)
{
	_frame.setPosition(pos);
	_frame.setTexture(*Resolver<sf::Texture>::resolve(name));
}

HUDPanel::~HUDPanel()
{

}

bool HUDPanel::update(const sf::Event &e)
{
	return (true);
}

void HUDPanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_frame);
}

//
// HUDDynamicPanel
//

HUDDraggablePanel::HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
	: HUDPanel(pos + sf::Vector2f(0, 15), size, frameColor)
{
	sf::Texture ctexture;

	_dragging = false;
	_header.setPosition(pos);
	ctexture.create(size.x, 15);
	_header.setTexture(ctexture);
	_header.setColor(headerColor);
}

HUDDraggablePanel::HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
	: HUDPanel(pos + sf::Vector2f(0, 15), size, frameResource)
{
	_dragging = false;
	_header.setPosition(pos);
	_header.setTexture(*Resolver<sf::Texture>::resolve(headerResource));
}


HUDDraggablePanel::~HUDDraggablePanel()
{

}

void HUDDraggablePanel::movePanel(const sf::Vector2f &newpos)
{
	_header.setPosition(newpos);
	_frame.setPosition(newpos + sf::Vector2f(0, _header.getLocalBounds().height));
}

bool HUDDraggablePanel::update(const sf::Event &e)
{
	HUDPanel::update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_dragging && e.key.code == sf::Mouse::Left && _header.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Engine::instance->getWindowHandle()))))
		{
			_dragging = true;
			_dragOffset = sf::Vector2f(sf::Mouse::getPosition(*Engine::instance->getWindowHandle()).x - _header.getGlobalBounds().left,
				sf::Mouse::getPosition(*Engine::instance->getWindowHandle()).y - _header.getGlobalBounds().top);
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (_dragging && e.key.code == sf::Mouse::Left)
			_dragging = false;
	}
	if (_dragging && e.type == sf::Event::MouseMoved)
		movePanel(sf::Vector2f(e.mouseMove.x - _dragOffset.x, e.mouseMove.y - _dragOffset.y));
	return (true);
}

void HUDDraggablePanel::draw(sf::RenderWindow *win)
{
	if (_active)
		win->draw(_header);
	HUDPanel::draw(win);
}
