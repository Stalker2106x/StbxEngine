#include "cengine.hh"

void f(void *menu)
{
	menu = new stb::Menu();
	static_cast<stb::Menu *>(menu)->loadFromFile("./Data/menu/GOLmon.xml");
}

sEngine::sEngine()
{
	std::vector<std::string> resolutions = {
		"800x600",
		"1024x768",
		"1920x1080"
	};
	
	stb::Menu::customAction.emplace("Settings", std::make_pair(f, &_mainMenu));
	stb::Menu::dynamicValue.emplace("Resolutions", resolutions);
	_mainMenu.loadFromFile("./Data/menu/main.xml");
	stb::GUIPanel *panel = gui->addDraggablePanel("windowz", sf::Vector2i(400, 200), sf::Color(64, 64, 64), sf::Color(110, 110, 110));
	panel->addElement(new stb::GUIIndicator<int>("Indicator :", _framerate));
}

bool sEngine::update(const sf::Event &e)
{
	_mainMenu.update(e);
	return (true);
}

void sEngine::draw()
{
	_mainMenu.draw(_win);
}
