#include "GUIElementPair.hh"
#include "Resolver.hh"

using namespace stb;

/*
 * GUIElementPair Base class
 */

GUIElementPair::GUIElementPair() : GUIElement("", Pair)
{

}

GUIElementPair::GUIElementPair(GUIElement *first, GUIElement *second) : GUIElement("", Pair)
{

}

GUIElementPair::~GUIElementPair()
{

}

void GUIElementPair::initialUpdate()
{

}

const sf::Vector2f &GUIElementPair::getPosition()
{
	return (_first->getPosition());
}

void GUIElementPair::setFirst(GUIElement *element)
{
	_first = element;
}

void GUIElementPair::setSecond(GUIElement *element)
{
	_second = element;
}

void GUIElementPair::setPosition(const sf::Vector2f &pos)
{
	//Not implemented
}

bool GUIElementPair::update(const sf::Event &e)
{
  if (!_active)
	  return (false);
  _first->update(e);
  _second->update(e);
  return (true);
}

void GUIElementPair::draw(sf::RenderWindow *win)
{
	_first->draw(win);
	_second->draw(win);
}