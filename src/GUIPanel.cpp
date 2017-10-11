#include "Engine.hpp"
#include "GUIPanel.hh"
#include "Resolver.hh"

using namespace stb;

//
// GUIPanel
//

GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color) : GUIElement(id), _buttonBar(Horizontal)
{
	sf::Texture ctexture;

	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name) : GUIElement(id), _buttonBar(Horizontal)
{
	_frame.setTexture(*Resolver<sf::Texture>::resolve(name));
	_frame.setScale(1 / size.x, 1 / size.y);
}

GUIPanel::~GUIPanel()
{

}

void GUIPanel::clear()
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		delete (_elements[i]);
	}
	_elements.clear();
}

void GUIPanel::setStyle(char style)
{
	_style = style;
}

void GUIPanel::addElement(GUIElement *element)
{
	sf::Vector2f pos = element->getPosition() - _frame.getPosition();
	if (pos.x < 0 || pos.y < 0)
		element->setPosition(_frame.getPosition());
	_elements.push_back(element);
}

void GUIPanel::setPosition(const sf::Vector2f &pos)
{
	sf::Vector2f oldpos = _frame.getPosition();
	_frame.setPosition(pos);
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->setPosition(sf::Vector2f(_elements[i]->getPosition().x + (pos.x - oldpos.x), _elements[i]->getPosition().y + (pos.y - oldpos.y)));
	}
}

void GUIPanel::setBackground(const std::string &resource)
{
	_frame.setTexture(*Resolver<sf::Texture>::resolve(resource));
}

const sf::Vector2f &GUIPanel::getPosition()
{
	return (_frame.getPosition());
}


bool GUIPanel::updateRT()
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->updateRT();
	return (true);
}

bool GUIPanel::update(const sf::Event &e)
{
	if (!GUIElement::update(e))
		return (false);
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->update(e);
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
	_header.setScale(1 / size.x, 1);
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
	if ((_style & PN_CLOSE) == PN_CLOSE)
	{
		GUISpriteButton *btn = _buttonBar.addSpriteButton("__close", "buttons", SpriteSkin(sf::IntRect(0, 0, 16, 16), sf::IntRect(0, 16, 16, 16)));
		btn->setClickCallback(std::bind(&GUIDraggablePanel::toggle, this));
	}
	if ((_style & PN_LOCK) == PN_LOCK)
	{
		GUIToggleSpriteButton *btn = _buttonBar.addToggleSpriteButton("__lock", "buttons", SpriteSkin(sf::IntRect(16, 0, 16, 16), sf::IntRect(16, 16, 16, 16)), SpriteSkin(sf::IntRect(48, 0, 16, 16), sf::IntRect(48, 16, 16, 16)));
		btn->setClickCallback(std::bind(&GUIDraggablePanel::toggleLock, this));
	}
	_buttonBar.invert();
	setPosition(sf::Vector2f(0, 0));
	_active = true;
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
	//toggleactiveskin
}

void GUIDraggablePanel::setPosition(const sf::Vector2f &pos)
{
	_header.setPosition(pos);
	GUIPanel::setPosition(pos + sf::Vector2f(0, _header.getGlobalBounds().height));
	_buttonBar.setPosition(sf::Vector2f(pos + sf::Vector2f(_header.getLocalBounds().width - 32, 0)));
}

bool GUIDraggablePanel::update(const sf::Event &e)
{
	if (!GUIPanel::update(e))
		return (false);
	_buttonBar.update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_lock && !_dragging && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left) && _header.getGlobalBounds().contains(Engine::getMousePosition()))
		{
			_dragging = true;
			_dragOffset = sf::Vector2f(Engine::getMousePosition().x - _header.getGlobalBounds().left,
				Engine::getMousePosition().y - _header.getGlobalBounds().top);
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (!_lock && _dragging && static_cast<int>(e.key.code) == static_cast<int>(sf::Mouse::Left))
			_dragging = false;
	}
	else if (e.type == sf::Event::MouseMoved)
	{
		if (!_lock && _dragging)
			setPosition(sf::Vector2f(e.mouseMove.x - _dragOffset.x, e.mouseMove.y - _dragOffset.y));
	}
	return (true);
}

void GUIDraggablePanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	win->draw(_header);
	_buttonBar.draw(win);
	GUIPanel::draw(win);
}