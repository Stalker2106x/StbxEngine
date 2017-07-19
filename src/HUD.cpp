#include "HUD.hh"
#include "Resolver.hh"
#include "Engine.hpp"

using namespace stb;

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

HUDPanel *HUD::addPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color)
{
	HUDPanel *panel = new HUDPanel(id, size, color);

	_elements.push_back(panel);
	return (panel);
}

HUDPanel *HUD::addPanel(const std::string &id, const sf::Vector2i &size, const std::string &resource)
{
	HUDPanel *panel = new HUDPanel(id, size, resource);

	_elements.push_back(panel);
	return (panel);
}

HUDDraggablePanel *HUD::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
{
	HUDDraggablePanel *panel = new HUDDraggablePanel(id, size, headerColor, frameColor);

	_elements.push_back(panel);
	return (panel);
}

HUDDraggablePanel *HUD::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
{
	HUDDraggablePanel *panel = new HUDDraggablePanel(id, size, headerResource, frameResource);

	_elements.push_back(panel);
	return (panel);
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