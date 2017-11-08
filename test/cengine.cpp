#include "cengine.hh"
#include "../include/Resolver.hh"

sEngine::sEngine()
{
	//Initialize paths
	stb::Resolver<sf::Font>::addLocation("./Data/font/");
	stb::Resolver<sf::Texture>::addLocation("./Data/texture/");
	stb::Resolver<stb::GUIScreen>::addLocation("./Data/screen/");
	//init engine
	init();
	//Setup GUI Defaults
	gui->defaults.font = "Console";
	gui->defaults.fontSize = 25;
	//Change none to any screen
	gui->changeScreen("main");
	//Add Draggable Panel
	std::shared_ptr<stb::GUIDraggablePanel> panel = std::make_shared<stb::GUIDraggablePanel>(nullptr, sf::Vector2i(400, 200), sf::Color(64, 64, 64), sf::Color(110, 110, 110));
	panel->setId("windowz");
	gui->addElement(panel);
	//Add FPS Indicator inside
	panel->addElement(std::make_shared<stb::GUIIndicator<int>>(panel->getSPtr(), "Indicator :", "glitch", _framerate));
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow *win)
{

}
