#include "Engine.hpp"
#include "GUIPanel.hh"
#include "Resolver.hh"

using namespace stb;

//
// GUIPanel
//

GUIPanel::GUIPanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const sf::Color &color) : GUIElement("", parent, ButtonBar), _buttonBar(getSPtr(), Horizontal)
{
	sf::Texture ctexture;

	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
	_spacing = 0;
}


GUIPanel::GUIPanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const std::string &name) : GUIElement("", parent, ButtonBar), _buttonBar(getSPtr(), Horizontal)
{
	_frame.setTexture(*SFResolver<sf::Texture>::resolve(name));
	_frame.setScale(1 / size.x, 1 / size.y);
	_spacing = 0;
}

GUIPanel::~GUIPanel()
{

}

void GUIPanel::initialUpdate()
{

}

void GUIPanel::clear()
{
	_elements.clear();
}

bool GUIPanel::removeElement(int index)
{
	if (index < 0 || index > _elements.size())
		return (false);
	if (_elements[index]->isActive())
		_elements[index]->toggle();
	_drop.push(index);
	return (true);
}

void GUIPanel::drop()
{
	while (!_drop.empty())
	{
		_elements.erase(_elements.begin() + _drop.top());
		_drop.pop();
	}
}

void GUIPanel::setStyle(char style)
{
	_style = style;
}

void GUIPanel::addElement(std::shared_ptr<GUIElement> element)
{
	sf::Vector2f pos = _frame.getPosition();

	if (element->getPosition() == sf::Vector2f(0, 0)) //If position is not specified, let the container arrange
	{
		for (size_t i = 0; i < _elements.size(); i++)
		{
			pos.y += _elements[i]->getSize().y + _spacing;
		}
		element->setPosition(pos);
	}
	_elements.push_back(element);
}

void GUIPanel::setPosition(const sf::Vector2f &pos)
{
	sf::Vector2f oldpos = _frame.getPosition();
	_frame.setPosition(pos);
	for (std::deque<std::shared_ptr<GUIElement>>::const_iterator it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->setPosition(sf::Vector2f((*it)->getPosition().x + (pos.x - oldpos.x), (*it)->getPosition().y + ((pos.y - oldpos.y) + _spacing)));
	}
}

void GUIPanel::setBackground(const std::string &resource, const sf::Color &color)
{
	std::shared_ptr<sf::Texture> texture = SFResolver<sf::Texture>::resolve(resource);
	if (texture == NULL)
		Engine::instance->console->output(COLOR_ERROR, "Panel: Error loading texture " + resource + " for panel " + _id);
	_frame.setTexture(*texture);
	_frame.setColor(color);
}

void GUIPanel::setSpacing(int spacing)
{
	_spacing = spacing;
}

const sf::Vector2f GUIPanel::getPosition() const
{
	return (_frame.getPosition());
}

const sf::Vector2f GUIPanel::getSize() const
{
	return (sf::Vector2f(_frame.getLocalBounds().width, _frame.getLocalBounds().height));
}

bool GUIPanel::updateRT()
{
	for (std::deque<std::shared_ptr<GUIElement>>::const_iterator it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->updateRT();
	}
	return (true);
}

bool GUIPanel::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	for (std::deque<std::shared_ptr<GUIElement>>::const_iterator it = _elements.begin(); it != _elements.end(); it++)
	{
		if (!(*it)->update(e))
			return (false);
	}
	drop(); //Discard deleted elements
	return (true);
}

void GUIPanel::draw(sf::RenderWindow &win)
{
	if (!_active)
		return;
	if (_frame.getTexture() != NULL)
		win.draw(_frame);
	for (std::deque<std::shared_ptr<GUIElement>>::const_iterator it = _elements.begin(); it != _elements.end(); it++)
	{
		(*it)->draw(win);
	}
}

//
// GUIDynamicPanel
//

GUIDraggablePanel::GUIDraggablePanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
	: GUIPanel(parent, size, frameColor)
{
	sf::Texture ctexture;

	ctexture.create(size.x, 15);
	_header.setTexture(ctexture);
	_header.setColor(headerColor);
	initialUpdate();
}

GUIDraggablePanel::GUIDraggablePanel(std::shared_ptr<GUIElement> parent, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
	: GUIPanel(parent, size, frameResource)
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
		std::shared_ptr<GUISpriteButton<GUIButton>> btn = std::make_shared<GUISpriteButton<GUIButton>>(_buttonBar.getSPtr(), "buttons");
		btn->setSkin(new SpriteSkin(sf::IntRect(0, 0, 16, 16), sf::IntRect(0, 16, 16, 16)));
		btn->setClickCallback(std::bind(&GUIDraggablePanel::toggle, this));
		_buttonBar.addButton(btn);
	}
	if ((_style & PN_LOCK) == PN_LOCK)
	{
		std::shared_ptr<GUISpriteButton<GUIToggleButton>> btn = std::make_shared<GUISpriteButton<GUIToggleButton>>(_buttonBar.getSPtr(), "buttons");
		btn->setSkin(new SpriteSkin(sf::IntRect(16, 0, 16, 16), sf::IntRect(16, 16, 16, 16)));
		btn->setAltSkin(new SpriteSkin(sf::IntRect(32, 0, 16, 16), sf::IntRect(32, 16, 16, 16)));
		btn->setClickCallback(std::bind(&GUIDraggablePanel::toggleLock, this));
		_buttonBar.addButton(btn);
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

void GUIDraggablePanel::draw(sf::RenderWindow &win)
{
	if (!_active)
		return;
	win.draw(_header);
	_buttonBar.draw(win);
	GUIPanel::draw(win);
}