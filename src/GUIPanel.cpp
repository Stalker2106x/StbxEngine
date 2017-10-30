#include "Engine.hpp"
#include "GUIPanel.hh"
#include "GUIMenu.hh"
#include "Resolver.hh"

using namespace stb;

//
// GUIPanel
//

GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color) : GUIElement(id, ButtonBar), _buttonBar(Horizontal)
{
	sf::Texture ctexture;

	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


GUIPanel::GUIPanel(const std::string &id, const sf::Vector2i &size, const std::string &name) : GUIElement(id, ButtonBar), _buttonBar(Horizontal)
{
	_frame.setTexture(*SFResolver<sf::Texture>::resolve(name));
	_frame.setScale(1 / size.x, 1 / size.y);
}

GUIPanel::~GUIPanel()
{

}

void GUIPanel::initialUpdate()
{

}

void GUIPanel::clear()
{
	for (auto it = _elements.begin(); it != _elements.end(); it++)
	{
		delete (*it);
	}
	_elements.clear();
}

void GUIPanel::drop()
{
	while (!_drop.empty())
	{
		if (_drop.front().second)
			delete (_elements.at(_drop.front().first));
		_elements.erase(_elements.begin() + _drop.front().first);
		_drop.pop();
	}
}

void GUIPanel::setStyle(char style)
{
	_style = style;
}

void GUIPanel::addElement(GUIElement *element)
{
	sf::Vector2f pos = _frame.getPosition();

	if (element->getPosition() == sf::Vector2f(0, 0)) //If position is not specified, let the container arrange
	{
		for (size_t i = 0; i < _elements.size(); i++)
		{
			pos.y += _elements[i]->getSize().y;
		}
		element->setPosition(pos);
	}
	_elements.push_back(element);
}

void GUIPanel::setPosition(const sf::Vector2f &pos)
{
	sf::Vector2f oldpos = _frame.getPosition();
	_frame.setPosition(pos);
	for (auto it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->setPosition(sf::Vector2f((*it)->getPosition().x + (pos.x - oldpos.x), (*it)->getPosition().y + (pos.y - oldpos.y)));
	}
}

void GUIPanel::setBackground(const std::string &resource)
{
	sf::Texture *texture = SFResolver<sf::Texture>::resolve(resource);
	if (texture == NULL)
		Engine::instance->console->output(COLOR_ERROR, "Panel: Error loading texture " + resource + " for panel " + _id);
	_frame.setTexture(*texture);
}

const sf::Vector2f GUIPanel::getPosition()
{
	return (_frame.getPosition());
}

const sf::Vector2f GUIPanel::getSize()
{
	return (sf::Vector2f(_frame.getLocalBounds().width, _frame.getLocalBounds().height));
}

bool GUIPanel::updateRT()
{
	for (auto it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->updateRT();
	}
	return (true);
}

bool GUIPanel::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	for (auto it = _elements.begin(); it != _elements.end(); it++)
	{
		if (!(*it)->update(e))
			return (false);
	}
	drop();
	return (true);
}

void GUIPanel::draw(sf::RenderWindow *win)
{
	if (!_active)
		return;
	if (_frame.getTexture() != NULL)
		win->draw(_frame);
	for (auto it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->draw(win);
	}
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
	_header.setTexture(*SFResolver<sf::Texture>::resolve(headerResource));
	_header.setScale(1 / size.x, 1 / 15);
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
		GUISpriteButton<GUIButton> *btn = _buttonBar.addSpriteButton("buttons");
		btn->setSkin(new SpriteSkin(sf::IntRect(0, 0, 16, 16), sf::IntRect(0, 16, 16, 16)));
		btn->setClickCallback(std::bind(&GUIDraggablePanel::toggle, this));
	}
	if ((_style & PN_LOCK) == PN_LOCK)
	{
		GUISpriteButton<GUIToggleButton> *btn = _buttonBar.addToggleSpriteButton("buttons");
		btn->setSkin(new SpriteSkin(sf::IntRect(16, 0, 16, 16), sf::IntRect(16, 16, 16, 16)));
		btn->setAltSkin(new SpriteSkin(sf::IntRect(32, 0, 16, 16), sf::IntRect(32, 16, 16, 16)));
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