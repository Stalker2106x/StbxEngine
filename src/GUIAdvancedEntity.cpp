#include "GUIAdvancedEntity.hh"
#include "GUIElement.hpp"

using namespace stb;

GUIScrollbar::GUIScrollbar(std::shared_ptr<GUIElement> parent) : GUIElement("", parent, Scrollbar)
{
	_upBtn = new GUISpriteButton<GUIButton>(NULL, "buttons");
	_dnBtn = new GUISpriteButton<GUIButton>(NULL, "buttons");
}

GUIScrollbar::~GUIScrollbar()
{

}

void GUIScrollbar::initialUpdate()
{

}

void GUIScrollbar::setPosition(const sf::Vector2f &pos)
{
	_container.setPosition(pos);
}

const sf::Vector2f GUIScrollbar::getSize()
{
	return (_container.getSize());
}

const sf::Vector2f GUIScrollbar::getPosition()
{
	return (_container.getPosition());
}

bool GUIScrollbar::update(const sf::Event &e)
{
	if (!_active)
		return (false);
	return (true);
}

void GUIScrollbar::draw(sf::RenderWindow *win)
{
	win->draw(_container);
	win->draw(_slider);
	_upBtn->draw(win);
	_dnBtn->draw(win);
}