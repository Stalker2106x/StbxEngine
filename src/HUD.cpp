#include "HUD.hh"
#include "Resolver.hh"
#include "Engine.hpp"

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

void HUDSIndicator::toggle()
{
	_active = (_active ? false : true);
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

	_active = true;
	_frame.setPosition(pos);
	ctexture.create(size.x, size.y);
	_frame.setTexture(ctexture);
	_frame.setColor(color);
}


HUDPanel::HUDPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &name)
{
	_active = true;
	_frame.setPosition(pos);
	_frame.setTexture(*Resolver<sf::Texture>::resolve(name));
}

HUDPanel::~HUDPanel()
{

}

void HUDPanel::toggle()
{
	_active = (_active ? false : true);
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

HUDDraggablePanel::HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor) : HUDPanel(pos, size, frameColor)
{
	_dragging = false;
}

HUDDraggablePanel::HUDDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource) : HUDPanel(pos, size, frameResource)
{
	_dragging = false;
}


HUDDraggablePanel::~HUDDraggablePanel()
{

}

bool HUDDraggablePanel::update(const sf::Event &e)
{
	HUDPanel::update(e);
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (!_dragging && e.key.code == sf::Mouse::Left && _header.getLocalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Engine::instance->getWindowHandle()))))
			_dragging = true;
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (_dragging && e.key.code == sf::Mouse::Left)
			_dragging = false;
	}
	if (_dragging && e.type == sf::Event::MouseMoved)
	{
		_header.move(e.mouseMove.x, e.mouseMove.y);
		_frame.move(e.mouseMove.x, e.mouseMove.y);
	}
	return (true);
}

void HUDDraggablePanel::draw(sf::RenderWindow *win)
{
	HUDPanel::draw(win);
	win->draw(_header);
}

//
// HUD
//

HUD::HUD()
{
	_active = true;
}

HUD::~HUD()
{

}

bool HUD::isActive()
{
	return (_active);
}

void HUD::toggle()
{
	_active = (_active ? false : true);
}

void HUD::addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color)
{
	_panels.push_back(new HUDPanel(pos, size, color));
}

void HUD::addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &resource)
{
	_panels.push_back(new HUDPanel(pos, size, resource));
}

void HUD::addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
{
	_panels.push_back(new HUDDraggablePanel(pos, size, headerColor, frameColor));
}

void HUD::addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
{
	_panels.push_back(new HUDDraggablePanel(pos, size, headerResource, frameResource));
}
void HUD::toggleHidePanel(const int &id)
{
	if (_panels.size() > id)
		_panels[id]->toggle();
	else
		Engine::console->output(COLOR_ERROR, "Error: No panel with id "+id);
}

void HUD::toggleHideIndicator(const int &id)
{
	if (_indicators.size() > id)
		_indicators[id]->toggle();
	else
		Engine::console->output(COLOR_ERROR, "Error: No indicator with id " + id);
}

bool HUD::update(sf::Event &e)
{
	return (true);
}

void HUD::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _panels.size(); i++)
		_panels[i]->draw(win);
	for (size_t i = 0; i < _indicators.size(); i++)
		_indicators[i]->draw(win);
}