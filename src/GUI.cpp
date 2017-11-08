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
	resetDefaults();
}

GUI::~GUI()
{

}

bool GUI::isActive()
{
	return (_active);
}

void GUI::resetDefaults()
{
	defaults.font = "Console";
	defaults.fontSize = 16;
	defaults.fontColor = "#255255255";
	defaults.pairSpacing = 10;
	defaults.panelSpacing = 5;
	defaults.gridSpacing = 5;
}

std::shared_ptr<GUIElement> GUI::getElement(const std::string &id)
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

void GUI::changeScreen(const std::string &resource, const std::string &location)
{
	static std::string lastLocation;
	std::shared_ptr<GUIScreen> newScreen;
	std::string resId, path;
	int index;

	for (index = 0; index < _elements.size() && _elements[index]->getType() != Screen; index++);
	if (location.empty() && lastLocation.empty())
	{
		newScreen = STBResolver<GUIScreen>::resolve(resource);
	}
	else
	{
		int sep;

		path = (location.empty() ? lastLocation : location);
		sep = path.find_last_of("/") + 1;
		resId = path.substr(sep, path.find_last_of(".") - sep);
		path.erase(path.find(resId), path.length() - path.find(resId));
		newScreen = STBResolver<GUIScreen>::resolve(resource, resId, path);
	}
	if (newScreen == NULL)
	{
		Engine::instance->console->output(COLOR_ERROR, "Screen: Error. Could not load screen \"" + resource + "\"");
		return;
	}
	lastLocation = (location.empty() ? path + resource + ".xml" : location);
	if (!newScreen->isActive())
	{
		newScreen->initialUpdate();
		newScreen->toggle();
	}
	if (index >= _elements.size())
		_elements.insert(_elements.begin(), newScreen);
	else
		_elements[index] = newScreen;
}

void GUI::toggle()
{
	_active = (_active ? false : true);
}

void GUI::addElement(std::shared_ptr<GUIElement> element)
{
	_elements.push_back(element);
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
	return (true);
}

void GUI::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _elements.size(); i++)
		_elements[i]->draw(win);
}
