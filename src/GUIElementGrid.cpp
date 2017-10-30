#include "GUIElementGrid.hh"

using namespace stb;

GUIElementGrid::GUIElementGrid(const sf::Vector2i &size) : GUIElement("", Grid)
{
	_size = size;
	_spacing = 0;
}

GUIElementGrid::~GUIElementGrid()
{

}

void GUIElementGrid::initialUpdate()
{

}

const sf::Vector2f GUIElementGrid::getPosition()
{
	if (_elements.size() > 0)
		return (_elements[0]->getPosition());
	return (sf::Vector2f(0, 0));
}

const sf::Vector2f GUIElementGrid::getSize()
{
	//tmp
	return (sf::Vector2f(0, 0));
}

void GUIElementGrid::pushElement(GUIElement *element)
{
	_elements.push_back(element);
}

void GUIElementGrid::setSpacing(int spacing)
{
	_spacing = spacing;
}

void GUIElementGrid::setPosition(const sf::Vector2f &pos)
{
	//tmp
}

bool GUIElementGrid::update(const sf::Event &e)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->update(e);
	}
	return (true);
}

void GUIElementGrid::draw(sf::RenderWindow *win)
{
	for (size_t i = 0; i < _elements.size(); i++)
	{
		_elements[i]->draw(win);
	}
}