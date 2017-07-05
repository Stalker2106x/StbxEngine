#include "cengine.hh"

sEngine::sEngine()
{
	_mainMenu.loadFromFile("./Data/menu/main.xml");
}

bool sEngine::update(sf::Event &e)
{
	_mainMenu.update(e);
	return (true);
}

void sEngine::draw()
{
	_mainMenu.draw(_win);
}
