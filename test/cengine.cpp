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
	stb::GUIDefaults.font = "Console";
	stb::GUIDefaults.fontSize = 25;
	//Change none to any screen
	gui->changeScreen("main");
	//Add Draggable Panel
	std::shared_ptr<stb::GUIDraggablePanel> panel = std::make_shared<stb::GUIDraggablePanel>(nullptr, sf::Vector2i(400, 200), sf::Color(64, 64, 64), sf::Color(110, 110, 110));
	panel->setId("windowz");
	panel->setPosition(sf::Vector2f(10, 10));
	gui->addElement(panel);
	//Create FPS Indicator inside
	std::shared_ptr<stb::GUIElementPair> pair = stb::GUIElementPair::make_pair(panel,
		std::make_shared<stb::GUIText>(nullptr, "Indicator :", "glitch"),
		std::make_shared<stb::GUIIndicator<int>>(nullptr, _framerate, "glitch"));
	pair->dock(stb::Direction::Right);
	panel->addElement(pair);
}

bool sEngine::update(const sf::Event &e)
{
	return (true);
}

void sEngine::draw(sf::RenderWindow &win)
{

}
