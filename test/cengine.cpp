#include "cengine.hh"

void f(void *menu)
{
	menu = new Menu();
	static_cast<Menu *>(menu)->loadFromFile("./Data/menu/settings.xml");
}

sEngine::sEngine()
{
	Menu::customAction.emplace("Settings", std::make_pair(f, &_mainMenu));
	_mainMenu.loadFromFile("./Data/menu/GOLmon.xml");
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
