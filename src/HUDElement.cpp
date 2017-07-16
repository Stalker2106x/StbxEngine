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

HUDPanel::HUDPanel()
{

}

HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color) : HUDPanel()
{
	sf::Texture ctexture;

	_frame.setPosition(pos);
	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &name) : HUDPanel()
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

	_header.setPosition(pos);
	ctexture.create(size.x, 15);
	_header.setTexture(ctexture);
	_header.setColor(headerColor);
	initialUpdate(pos);
}

HUDDraggablePanel::HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
	: HUDPanel(pos + sf::Vector2f(0, 15), size, frameResource)
{
	_header.setPosition(pos);
	_header.setTexture(*Resolver<sf::Texture>::resolve(headerResource));
	initialUpdate(pos);
}


HUDDraggablePanel::~HUDDraggablePanel()
{

}

void HUDDraggablePanel::initialUpdate(const sf::Vector2f &pos)
{
	_lock = false;
	_dragging = false;
	_style |= PN_CLOSE | PN_LOCK;
	_bhover[Close] = false;
	_bhover[Lock] = false;
	_buttonBar[Close].setTexture(*Resolver<sf::Texture>::resolve("buttons"));
	_buttonBar[Close].setTextureRect(sf::IntRect(0, 0, 16, 16));
	_buttonBar[Close].setPosition(pos + sf::Vector2f(_header.getLocalBounds().width - _buttonBar[Close].getLocalBounds().width, 0));
	_buttonBar[Lock].setTexture(*Resolver<sf::Texture>::resolve("buttons"));
	_buttonBar[Lock].setTextureRect(sf::IntRect(32, 0, 16, 16));
	_buttonBar[Lock].setPosition(pos + sf::Vector2f(_header.getLocalBounds().width -
		(_buttonBar[Close].getLocalBounds().width + _buttonBar[Lock].getLocalBounds().width), 0));
}


void HUDDraggablePanel::toggleLock()
{
	_lock = (_lock ? false : true);
	if (_lock)
		_buttonBar[Lock].setTextureRect(sf::IntRect(16, 0, 16, 16));
	else
		_buttonBar[Lock].setTextureRect(sf::IntRect(32, 0, 16, 16));
}

void HUDDraggablePanel::setStyle(const char &style)
{
	_style = style;
}

void HUDDraggablePanel::movePanel(const sf::Vector2f &newpos)
{
	_header.setPosition(newpos);
	_buttonBar[Close].setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width - _buttonBar[0].getGlobalBounds().width, 0));
	_buttonBar[Lock].setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width -
		(_buttonBar[Close].getGlobalBounds().width + _buttonBar[Lock].getGlobalBounds().width), 0));
	_frame.setPosition(newpos + sf::Vector2f(0, _header.getGlobalBounds().height));
}

bool HUDDraggablePanel::onButtonHover(const PanelButton &id, const bool &triggered)
{
	if ((triggered && _bhover[id])
		|| (!triggered && !_bhover[id]))
		return (false);
	if (triggered)
	{
		_bhover[id] = true;
		if (id == Close)
			_buttonBar[id].setTextureRect(sf::IntRect(0, 16, 16, 16));
		else if (id == Lock)
		{
			if (_lock)
				_buttonBar[id].setTextureRect(sf::IntRect(16, 16, 16, 16));
			else
				_buttonBar[id].setTextureRect(sf::IntRect(32, 16, 16, 16));
		}
	}
	else
	{
		_bhover[id] = false;
		if (id == Close)
			_buttonBar[id].setTextureRect(sf::IntRect(0, 0, 16, 16));
		else if (id == Lock)
		{
			if (_lock)
				_buttonBar[id].setTextureRect(sf::IntRect(16, 0, 16, 16));
			else
				_buttonBar[id].setTextureRect(sf::IntRect(32, 0, 16, 16));
		}
	}
	return (true);
}

bool HUDDraggablePanel::update(const sf::Event &e)
{
	HUDPanel::update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_lock && !_dragging && e.key.code == sf::Mouse::Left && _header.getGlobalBounds().contains(Engine::getMousePosition()))
		{
			_dragging = true;
			_dragOffset = sf::Vector2f(Engine::getMousePosition().x - _header.getGlobalBounds().left,
				Engine::getMousePosition().y - _header.getGlobalBounds().top);
		}
		if ((_style & PN_CLOSE) == PN_CLOSE && _bhover[Close] && e.key.code == sf::Mouse::Left)
			toggle();
		if ((_style & PN_LOCK) == PN_LOCK && _bhover[Lock] && e.key.code == sf::Mouse::Left)
			toggleLock();
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (!_lock && _dragging && e.key.code == sf::Mouse::Left)
			_dragging = false;
	}
	if (e.type == sf::Event::MouseMoved)
	{
		if (!_lock && _dragging)
			movePanel(sf::Vector2f(e.mouseMove.x - _dragOffset.x, e.mouseMove.y - _dragOffset.y));
		if ((_style & PN_CLOSE) == PN_CLOSE && _buttonBar[Close].getGlobalBounds().contains(Engine::getMousePosition()))
			onButtonHover(Close, true);
		else
			onButtonHover(Close, false);
		if ((_style & PN_LOCK) == PN_LOCK && _buttonBar[Lock].getGlobalBounds().contains(Engine::getMousePosition()))
			onButtonHover(Lock, true);
		else
			onButtonHover(Lock, false);
	}
	return (true);
}

void HUDDraggablePanel::draw(sf::RenderWindow *win)
{
	if (_active)
	{
		win->draw(_header);
		if ((_style & PN_CLOSE) == PN_CLOSE)
			win->draw(_buttonBar[Close]);
		if ((_style & PN_LOCK) == PN_LOCK)
			win->draw(_buttonBar[Lock]);
	}
	HUDPanel::draw(win);
}
