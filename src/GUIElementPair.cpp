#include "GUIElementPair.hh"
#include "Resolver.hh"

using namespace stb;

GUIElementPair::GUIElementPair(GUIElement *first, GUIElement *second) : GUIElement("", Pair)
{

}

GUIElementPair::~GUIElementPair()
{

}

void GUIElementPair::initialUpdate()
{
	_spacing = 0;
}

const sf::Vector2f GUIElementPair::getPosition()
{
	return (_first->getPosition());
}

const sf::Vector2f GUIElementPair::getSize()
{
	return (_first->getSize() + sf::Vector2f(_spacing, 0) + _second->getSize());
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
	_first->setPosition(pos);
	_second->setPosition(pos + sf::Vector2f(_spacing /* + _first->getSize().x */, 0)); //tmp
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