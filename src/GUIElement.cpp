#include "GUIElement.hh"
#include "Engine.hpp"

using namespace stb;

//
// GUIElement
//

GUIElement::GUIElement(const std::string &id)
{
	_id = id;
	_active = true;
}

void GUIElement::toggle()
{
	_active = (_active ? false : true);
}

const std::string &GUIElement::getId()
{
	return (_id);
}

bool GUIElement::updateRT()
{
	return (true);
}

bool GUIElement::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	return (true);
}

//
// GUIButton
//

GUIButton::GUIButton(const std::string &id) : GUIElement(id)
{
}

GUIButton::~GUIButton()
{
}

bool GUIButton::onHover(const bool &triggered)
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

bool GUIButton::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	return (true);
}

void GUIButton::draw(sf::RenderWindow *win)
{

}

//
// GUITextButton
//

GUITextButton::GUITextButton(const std::string &id, const std::string &label, const sf::Vector2f &pos) : GUIButton(id)
{
	_label.setString(label);
}

GUITextButton::~GUITextButton()
{
}

bool GUITextButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	if (e.type == sf::Event::MouseMoved)
	{
		if (_label.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
			onHover(true);
		else
			onHover(false);
	}
	return (true);
}

void GUITextButton::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_label);
}

//
// GUISpriteButton
//

GUISpriteButton::GUISpriteButton(const std::string &id, const std::string &resource, const sf::Vector2f &pos) : GUIButton(id)
{
}

GUISpriteButton::~GUISpriteButton()
{
}

bool GUISpriteButton::update(const sf::Event &e)
{
	if (!GUIButton::update(e))
		return (false);
	if (e.type == sf::Event::MouseMoved)
	{
		if (_sprite.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
			onHover(true);
		else
			onHover(false);
	}
	return (true);
}

void GUISpriteButton::draw(sf::RenderWindow *win)
{

}

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

void GUISIndicator::setFontsize(const int &fontSize)
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
// GUIPanel
//

GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color) : GUIElement(id)
{
	sf::Texture ctexture;

	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name) : GUIElement(id)
{
	_frame.setTexture(*Resolver<sf::Texture>::resolve(name));
}

GUIPanel::~GUIPanel()
{

}

void GUIPanel::setPosition(const sf::Vector2f &pos)
{
	_frame.setPosition(pos);
}

void GUIPanel::setStyle(const char &style)
{
	_style = style;
}

void GUIPanel::addElement(GUIElement *element)
{
	_elements.push_back(element);
	_elements.back()->setPosition(_frame.getPosition() + sf::Vector2f(5, 5 + ((_elements.size() - 1) * 35)));
}

void GUIPanel::updateElementsPosition()
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->setPosition(_frame.getPosition() + sf::Vector2f(5, 5 + (i * 35)));
	}
}

bool GUIPanel::onButtonHover(const PanelButton &id, const bool &triggered)
{
	if ((triggered && _bhover[id])
		|| (!triggered && !_bhover[id]))
		return (false);
	if (triggered)
	{
		_bhover[id] = true;
		if (id == Close)
			_buttonBar[id].setTextureRect(sf::IntRect(0, 16, 16, 16));
	}
	else
	{
		_bhover[id] = false;
		if (id == Close)
			_buttonBar[id].setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	return (true);
}

bool GUIPanel::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if ((_style & PN_CLOSE) == PN_CLOSE && _bhover[Close] && e.key.code == sf::Mouse::Left)
			toggle();
	}
	else if (e.type == sf::Event::MouseMoved)
	{
		if ((_style & PN_CLOSE) == PN_CLOSE && _buttonBar[Close].getGlobalBounds().contains(Engine::getMousePosition()))
			onButtonHover(Close, true);
		else
			onButtonHover(Close, false);
	}
	return (true);
}

void GUIPanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_frame);
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->draw(win);
}

//
// GUIDynamicPanel
//

GUIDraggablePanel::GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
	: GUIPanel(id, size, frameColor)
{
	sf::Texture ctexture;

	ctexture.create(size.x, 15);
	_header.setTexture(ctexture);
	_header.setColor(headerColor);
	initialUpdate();
}

GUIDraggablePanel::GUIDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
	: GUIPanel(id, size, frameResource)
{
	_header.setTexture(*Resolver<sf::Texture>::resolve(headerResource));
	initialUpdate();
}


GUIDraggablePanel::~GUIDraggablePanel()
{

}

void GUIDraggablePanel::initialUpdate()
{
	_lock = false;
	_dragging = false;
	_style |= PN_CLOSE | PN_LOCK;
	_bhover[Close] = false;
	_bhover[Lock] = false;
	_buttonBar[Close].setTexture(*Resolver<sf::Texture>::resolve("buttons"));
	_buttonBar[Close].setTextureRect(sf::IntRect(0, 0, 16, 16));
	_buttonBar[Lock].setTexture(*Resolver<sf::Texture>::resolve("buttons"));
	_buttonBar[Lock].setTextureRect(sf::IntRect(32, 0, 16, 16));
	movePanel(sf::Vector2f(0,0));
}

void GUIDraggablePanel::toggle()
{
	GUIElement::toggle();
	_dragging = false;
	_lock = false;
}

void GUIDraggablePanel::toggleLock()
{
	_lock = (_lock ? false : true);
	if (_lock)
		_buttonBar[Lock].setTextureRect(sf::IntRect(16, 0, 16, 16));
	else
		_buttonBar[Lock].setTextureRect(sf::IntRect(32, 0, 16, 16));
}

void GUIDraggablePanel::setPosition(const sf::Vector2f &pos)
{
	GUIPanel::setPosition(pos + sf::Vector2f(0, 15));
	_header.setPosition(pos);
	_buttonBar[Close].setPosition(pos + sf::Vector2f(_header.getLocalBounds().width - _buttonBar[Close].getLocalBounds().width, 0));
	_buttonBar[Lock].setPosition(pos + sf::Vector2f(_header.getLocalBounds().width -
		(_buttonBar[Close].getLocalBounds().width + _buttonBar[Lock].getLocalBounds().width), 0));
	movePanel(pos);
}

void GUIDraggablePanel::movePanel(const sf::Vector2f &newpos)
{
	_header.setPosition(newpos);
	_buttonBar[Close].setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width - _buttonBar[0].getGlobalBounds().width, 0));
	_buttonBar[Lock].setPosition(newpos + sf::Vector2f(_header.getGlobalBounds().width -
		(_buttonBar[Close].getGlobalBounds().width + _buttonBar[Lock].getGlobalBounds().width), 0));
	_frame.setPosition(newpos + sf::Vector2f(0, _header.getGlobalBounds().height));
	updateElementsPosition();
}

bool GUIDraggablePanel::onButtonHover(const PanelButton &id, const bool &triggered)
{
	if (!GUIPanel::onButtonHover(id, triggered))
		return (false);
	if (triggered)
	{
		if (id == Lock)
		{
			if (_lock)
				_buttonBar[id].setTextureRect(sf::IntRect(16, 16, 16, 16));
			else
				_buttonBar[id].setTextureRect(sf::IntRect(32, 16, 16, 16));
		}
	}
	else
	{
		if (id == Lock)
		{
			if (_lock)
				_buttonBar[id].setTextureRect(sf::IntRect(16, 0, 16, 16));
			else
				_buttonBar[id].setTextureRect(sf::IntRect(32, 0, 16, 16));
		}
	}
	return (true);
}

bool GUIDraggablePanel::update(const sf::Event &e)
{
	if (!GUIPanel::update(e))
		return (false);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_lock && !_dragging && e.key.code == sf::Mouse::Left && _header.getGlobalBounds().contains(Engine::getMousePosition()))
		{
			_dragging = true;
			_dragOffset = sf::Vector2f(Engine::getMousePosition().x - _header.getGlobalBounds().left,
				Engine::getMousePosition().y - _header.getGlobalBounds().top);
		}
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
		if ((_style & PN_LOCK) == PN_LOCK && _buttonBar[Lock].getGlobalBounds().contains(Engine::getMousePosition()))
			onButtonHover(Lock, true);
		else
			onButtonHover(Lock, false);
	}
	return (true);
}

void GUIDraggablePanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
		win->draw(_header);
		if ((_style & PN_CLOSE) == PN_CLOSE)
			win->draw(_buttonBar[Close]);
		if ((_style & PN_LOCK) == PN_LOCK)
			win->draw(_buttonBar[Lock]);
	GUIPanel::draw(win);
}
