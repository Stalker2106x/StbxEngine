#include "GUIContainer.hh"

using namespace stb;

//
// GUIElementPair
//

GUIElementPair::GUIElementPair(GUIElement *parent, GUIElement *first, GUIElement *second) : GUIElement("", parent, Pair)
{
	_spacing = 0;
}

GUIElementPair::~GUIElementPair()
{

}

void GUIElementPair::initialUpdate()
{
}

const sf::Vector2f GUIElementPair::getPosition()
{
	return (_first->getPosition());
}

const sf::Vector2f GUIElementPair::getSize()
{
	sf::Vector2f first = (_first == NULL ? sf::Vector2f(0, 0) : _first->getSize());
	sf::Vector2f second = (_second == NULL ? sf::Vector2f(0, 0) : _second->getSize());

	return (sf::Vector2f(first.x + _spacing + second.x, (first.y > second.y ? first.y : second.y)));
}

void GUIElementPair::setFirst(GUIElement *element)
{
	_first = element;
}

void GUIElementPair::setSecond(GUIElement *element)
{
	_second = element;
}

void GUIElementPair::setSpacing(int spacing)
{
	_spacing = spacing;
}


void GUIElementPair::setPosition(const sf::Vector2f &pos)
{
	if (_first != NULL)
		_first->setPosition(pos);
	if (_second != NULL)
		_second->setPosition(pos + sf::Vector2f(_spacing + _first->getSize().x, 0));
}

bool GUIElementPair::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	if (_first != NULL)
		_first->update(e);
	if (_second != NULL)
		_second->update(e);
	return (true);
}

void GUIElementPair::draw(sf::RenderWindow *win)
{
	if (_first != NULL)
		_first->draw(win);
	if (_second != NULL)
		_second->draw(win);
}

//
// GUIElementGrid
//

GUIElementGrid::GUIElementGrid(GUIElement *parent, const sf::Vector2i &size) : GUIElement("", parent, Grid)
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