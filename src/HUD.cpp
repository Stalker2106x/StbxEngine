#include "HUD.hh"
#include "Resolver.hh"
#include "Engine.hpp"

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

HUDElement *HUD::getElement(const std::string &id)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
			return (_elements[i]);
	}
	return (NULL);
}

void HUD::toggle()
{
	_active = (_active ? false : true);
}

void HUD::addPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color)
{
	_elements.push_back(new HUDPanel(id, size, color));
}

void HUD::addPanel(const std::string &id, const sf::Vector2i &size, const std::string &resource)
{
	_elements.push_back(new HUDPanel(id, size, resource));
}

void HUD::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
{
	_elements.push_back(new HUDDraggablePanel(id, size, headerColor, frameColor));
}

void HUD::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
{
	_elements.push_back(new HUDDraggablePanel(id, size, headerResource, frameResource));
}

void HUD::toggleHideElement(const std::string &id)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
		{
			_elements[i]->toggle();
			return;
		}
	}
	Engine::console->output(COLOR_ERROR, "Error: No HUD element with id: "+id);
}

bool HUD::update(sf::Event &e)
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->update(e);
	return (true);
}

void HUD::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->draw(win);
}