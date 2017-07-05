#include "cengine.hh"

bool sEngine::update(sf::Event &e)
{
	_mainMenu.update(e);
	return (true);
}

void sEngine::draw()
{
	_mainMenu.draw(_win);
}
