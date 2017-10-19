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

bool GUI::removeElement(const std::string &id, bool del)
{
	if (id.empty())
		return (false);
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getId() == id)
		{
			if (_elements[i]->isActive())
				_elements[i]->toggle();
			_drop.push(std::make_pair(i, del));
		}
	}
	return (true);
}

bool GUI::removeElement(int index, bool del)
{
	if (index < 0 || index > _elements.size())
		return (false);
	if (_elements[index]->isActive())
		_elements[index]->toggle();
	_drop.push(std::make_pair(index, del));
	return (true);
}

void GUI::drop()
{
	while (!_drop.empty())
	{
		if (_drop.top().second)
			delete (_elements.at(_drop.top().first));
		_elements.erase(_elements.begin() + _drop.top().first);
		_drop.pop();
	}
}

void GUI::changeScreen(const std::string &resource, const std::string &location)
{
	int oldScreenIndex = 0;

	for (size_t i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getType() == Screen)
		{
			removeElement(i + 1); //New screen will be inserted at previous index so we need to erase the next one
			oldScreenIndex = i;
		}
	}
	if (location.empty())
	{
		GUIScreen *newScreen = STBResolver<GUIScreen>::resolve(resource);
		newScreen->reset();
		if (!newScreen->isActive())
			newScreen->toggle();
		_elements.insert(_elements.begin() + oldScreenIndex, newScreen);
	}
	else
	{
		std::string resId, path;
		int sep;

		path = location;
		sep = location.find_last_of("/") + 1;
		resId = location.substr(sep, location.find_last_of(".") - sep);
		path.erase(location.find(resId), location.length() - location.find(resId));
		GUIScreen *newScreen = STBResolver<GUIScreen>::resolve(resId, path, resource);
		if (!newScreen->isActive())
			newScreen->toggle();
		newScreen->reset();
		_elements.insert(_elements.begin() + oldScreenIndex, newScreen);
	}
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
		_elements[i]->updateRT();
	return (true);
}

bool GUI::update(const sf::Event &e)
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->update(e);
	drop();
	return (true);
}

void GUI::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->draw(win);
}
