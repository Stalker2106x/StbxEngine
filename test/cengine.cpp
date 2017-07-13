#include "cengine.hh"

void f(void *menu)
{
	menu = new Menu();
	static_cast<Menu *>(menu)->loadFromFile("./Data/menu/GOLmon.xml");
}

sEngine::sEngine()
{
	std::vector<std::string> resolutions;

	resolutions.push_back("800x600");
	resolutions.push_back("1920x1080");
	Menu::customAction.emplace("Settings", std::make_pair(f, &_mainMenu));
	Menu::dynamicValue.emplace("Resolutions", resolutions);
	_mainMenu.loadFromFile("./Data/menu/main.xml");
	hud->addDraggablePanel(sf::Vector2f(0, 0), sf::Vector2f(400, 200), sf::Color::Cyan, sf::Color::Blue);
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
