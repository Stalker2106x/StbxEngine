#include "GUI.hh"
#include "Resolver.hh"
#include "Engine.hpp"
#include "GUIScreen.hh"

using namespace stb;

//
// GUI
//

GUI::GUI()
{
	_active = true;
}

GUI::~GUI()
{

}

bool GUI::isActive()
{
	return (_active);
}

GUIElement *GUI::getElement(const std::string &id)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
			return (_elements[i]);
	}
	return (NULL);
}

GUIElement *GUI::removeElement(const std::string &id, bool del)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
		{
			if (del);
				delete (_elements[i]);
			_elements.erase(_elements.begin() + i);
		}
	}
	return (NULL);
}

void GUI::changeScreen(const std::string &resource, const std::string &location)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getType() == Screen)
		{
			removeElement(_elements[i]->getId());
		}
	}
	_elements.push_back(Resolver<GUIScreen>::resolve(resource, location));
}

void GUI::toggle()
{
	_active = (_active ? false : true);
}

GUIPanel *GUI::addPanel(const std::string &id, const sf::Vector2i &size, const sf::Color &color)
{
	GUIPanel *panel = new GUIPanel(id, size, color);

	_elements.push_back(panel);
	return (panel);
}

GUIPanel *GUI::addPanel(const std::string &id, const sf::Vector2i &size, const std::string &resource)
{
	GUIPanel *panel = new GUIPanel(id, size, resource);

	_elements.push_back(panel);
	return (panel);
}

GUIDraggablePanel *GUI::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const sf::Color &headerColor, const sf::Color &frameColor)
{
	GUIDraggablePanel *panel = new GUIDraggablePanel(id, size, headerColor, frameColor);

	_elements.push_back(panel);
	return (panel);
}

GUIDraggablePanel *GUI::addDraggablePanel(const std::string &id, const sf::Vector2i &size, const std::string &headerResource, const std::string &frameResource)
{
	GUIDraggablePanel *panel = new GUIDraggablePanel(id, size, headerResource, frameResource);

	_elements.push_back(panel);
	return (panel);
}

void GUI::toggleHideElement(const std::string &id)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
		{
			_elements[i]->toggle();
			return;
		}
	}
	Engine::instance->console->output(COLOR_ERROR, "Error: No GUI element with id: "+id);
}

bool GUI::updateRT()
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->updateRT();
	}
	return (true);
}

bool GUI::update(const sf::Event &e)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->update(e);
	}
	return (true);
}

void GUI::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->draw(win);
	}
}
