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

void HUD::toggle()
{
	_active = (_active ? false : true);
}

void HUD::addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &color)
{
	_elements.push_back(new HUDPanel(pos, size, color));
}

void HUD::addPanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &resource)
{
	_elements.push_back(new HUDPanel(pos, size, resource));
}

void HUD::addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
{
	_elements.push_back(new HUDDraggablePanel(pos, size, headerColor, frameColor));
}

void HUD::addDraggablePanel(const sf::Vector2f &pos, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
{
	_elements.push_back(new HUDDraggablePanel(pos, size, headerResource, frameResource));
}

void HUD::toggleHideElement(const int &id)
{
	if (_elements.size() > id)
		_elements[id]->toggle();
	else
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